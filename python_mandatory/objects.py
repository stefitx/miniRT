# objects.py
import numpy as np
from utils import normalize

class Ray:
    def __init__(self, origin, direction):
        self.origin = np.array(origin)
        self.direction = normalize(np.array(direction))

class Sphere:
    def __init__(self, center, radius, color):
        self.center = np.array(center)
        self.radius = radius
        self.color = np.array(color)

    def intersect(self, ray):
        """Checks for intersection with a ray and returns the distance if it intersects."""
        oc = ray.origin - self.center
        a = np.dot(ray.direction, ray.direction)
        b = 2.0 * np.dot(oc, ray.direction)
        c = np.dot(oc, oc) - self.radius**2
        discriminant = b**2 - 4*a*c
        if discriminant > 0:
            t1 = (-b - np.sqrt(discriminant)) / (2.0 * a)
            t2 = (-b + np.sqrt(discriminant)) / (2.0 * a)
            if t1 > 0:
                return t1
            if t2 > 0:
                return t2
        return None

class Plane:
    def __init__(self, point, normal, color):
        self.point = np.array(point)        # Point on the plane
        self.normal = normalize(np.array(normal))  # Normal to the plane
        self.color = np.array(color)        # Color of the plane

    def intersect(self, ray):
        """Check for intersection with a plane and return the distance."""
        denom = np.dot(self.normal, ray.direction)
        if np.abs(denom) > 1e-6:  # Check that ray is not parallel to the plane
            t = np.dot(self.point - ray.origin, self.normal) / denom
            if t >= 0:
                return t
        return None


class Cylinder:
    def __init__(self, center, axis, radius, height, color):
        self.center = np.array(center)          # Base center of the cylinder
        self.axis = normalize(np.array(axis))   # Direction of the cylinder's axis
        self.radius = radius                     # Radius of the cylinder
        self.height = height                     # Height of the cylinder
        self.color = np.array(color)             # Color of the cylinder

    def intersect(self, ray):
        """Check for intersection with a finite cylinder and return the distance if it intersects."""
        dp = ray.origin - self.center
        dp_dot_axis = np.dot(dp, self.axis)
        d_dot_axis = np.dot(ray.direction, self.axis)
        a = np.dot(ray.direction, ray.direction) - d_dot_axis ** 2
        b = 2 * (np.dot(ray.direction, dp) - d_dot_axis * dp_dot_axis)
        c = np.dot(dp, dp) - dp_dot_axis ** 2 - self.radius ** 2
        discriminant = b ** 2 - 4 * a * c

        if discriminant > 0:
            sqrt_discriminant = np.sqrt(discriminant)
            t1 = (-b - sqrt_discriminant) / (2.0 * a)
            t2 = (-b + sqrt_discriminant) / (2.0 * a)
            
            # Calculate the intersection points in cylinder space
            y1 = dp_dot_axis + t1 * d_dot_axis
            y2 = dp_dot_axis + t2 * d_dot_axis

            if 0 <= y1 <= self.height and t1 > 0:
                return t1
            if 0 <= y2 <= self.height and t2 > 0:
                return t2
        
        return None

    def normal_at(self, point):
        """Calculate the normal vector at a given point on the cylinder surface."""
        dp = point - self.center
        dp_dot_axis = np.dot(dp, self.axis)
        return normalize(dp - dp_dot_axis * self.axis)


class Paraboloid:
    def __init__(self, vertex, axis, k, color):
        self.vertex = np.array(vertex)
        self.axis = normalize(np.array(axis))
        self.k = k  # Coefficient for the paraboloid equation
        self.color = np.array(color)

    def intersect(self, ray):
        """Checks for intersection with a ray and returns the distance if it intersects."""
        dp = ray.origin - self.vertex
        d_dot_axis = np.dot(ray.direction, self.axis)
        dp_dot_axis = np.dot(dp, self.axis)
        a = np.dot(ray.direction, ray.direction) - self.k * d_dot_axis ** 2
        b = 2 * (np.dot(ray.direction, dp) - self.k * d_dot_axis * dp_dot_axis)
        c = np.dot(dp, dp) - self.k * dp_dot_axis ** 2
        discriminant = b ** 2 - 4 * a * c
        if discriminant > 0:
            t1 = (-b - np.sqrt(discriminant)) / (2.0 * a)
            t2 = (-b + np.sqrt(discriminant)) / (2.0 * a)
            if t1 > 0:
                return t1
            if t2 > 0:
                return t2
        return None

class Light:
    def __init__(self, position, intensity):
        self.position = np.array(position)
        self.intensity = intensity

class Camera:
    def __init__(self, position, direction, fov):
        self.position = np.array(position)
        self.direction = normalize(np.array(direction))
        self.fov = fov

class Scene:
    def __init__(self, camera, image_width, image_height, ambient_intensity=0.2):
        self.objects = []
        self.lights = []
        self.camera = camera
        self.image_width = image_width
        self.image_height = image_height
        self.ambient_intensity = ambient_intensity  # Fixed ambient light intensity

    def add_object(self, obj):
        self.objects.append(obj)

    def add_light(self, light):
        self.lights.append(light)

    def trace_ray(self, ray):
        """Traces the ray and returns the color of the closest object."""
        closest_dist = float('inf')
        closest_object = None
        for obj in self.objects:
            dist = obj.intersect(ray)
            if dist and dist < closest_dist:
                closest_dist = dist
                closest_object = obj

        if closest_object is None:
            return np.array([0, 0, 0])  # Background color (black)

        # Calculate hit point
        hit_point = ray.origin + closest_dist * ray.direction

        # Calculate normal based on object type
        if isinstance(closest_object, Sphere):
            normal = normalize(hit_point - closest_object.center)
        elif isinstance(closest_object, Plane):
            normal = closest_object.normal
        elif isinstance(closest_object, Cylinder):
            normal = closest_object.normal_at(hit_point)  # Normal for cylinder surface

        color = np.zeros(3)

        # Add ambient light contribution
        ambient_light = closest_object.color * self.ambient_intensity
        color += ambient_light

        # Add diffuse lighting
        for light in self.lights:
            to_light = normalize(light.position - hit_point)
            diffuse_intensity = max(0, np.dot(to_light, normal)) * light.intensity
            color += closest_object.color * diffuse_intensity

        return np.clip(color, 0, 255)



    def render(self):
        """Renders the scene and returns an image array."""
        image = np.zeros((self.image_height, self.image_width, 3), dtype=np.uint8)
        aspect_ratio = self.image_width / self.image_height
        scale = np.tan(np.radians(self.camera.fov * 0.5))

        # Camera setup: Calculate camera right and up vectors
        camera_right = normalize(np.cross(self.camera.direction, np.array([0, 1, 0])))
        camera_up = normalize(np.cross(camera_right, self.camera.direction))

        for y in range(self.image_height):
            for x in range(self.image_width):
                # NDC coordinates
                ndc_x = (2 * (x + 0.5) / self.image_width - 1) * aspect_ratio
                ndc_y = (1 - 2 * (y + 0.5) / self.image_height)
                
                # Direction of the ray
                ray_direction = normalize(
                    self.camera.direction + ndc_x * camera_right * scale + ndc_y * camera_up * scale
                )
                ray = Ray(self.camera.position, ray_direction)
                
                # Trace the ray and set pixel color
                color = self.trace_ray(ray)
                image[y, x] = color

        return image
-