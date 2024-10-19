# main.py
from PIL import Image
from objects import Ray, Sphere, Light, Scene, Camera, Plane, Cylinder  # Import Plane class

def main():
    width, height = 800, 600
    fov = 90
    camera_position = [0, 0, 600]
    camera_direction = [0, 0, -1]  # Looking towards the negative z-axis

    camera = Camera(camera_position, camera_direction, fov)
    ambient_intensity = 0.1  # Adjust this to control the brightness of the ambient light
    ambient_color = [255, 255, 255]  # Ambient light color (white)
    
    scene = Scene(camera, width, height)
    
    # Add a paraboloid
    # paraboloid_vertex = [0, -100, 200]  # Vertex of the paraboloid
    # paraboloid_axis = [0, 1, 0]  # Axis pointing up
    # paraboloid_k = 0.01  # Coefficient for the paraboloid equation
    # paraboloid_color = [255, 255, 0]  # Yellow paraboloid
    # paraboloid = Paraboloid(paraboloid_vertex, paraboloid_axis, paraboloid_k, paraboloid_color)
    # scene.add_object(paraboloid)
    
    # Add a sphere
    sphere_center = [100.0, -50.0, 200]
    sphere_radius = 50  # Sphere radius
    sphere_color = [255, 0, 0]  # Red sphere
    sphere = Sphere(sphere_center, sphere_radius, sphere_color)
    scene.add_object(sphere)
    
    # Add a plane
    plane_point = [0.0, -100.0, 0]  # Plane position
    plane_normal = [0, 1, 0]  # Normal pointing upwards
    plane_color = [255, 255, 255]  # White plane
    plane = Plane(plane_point, plane_normal, plane_color)
    scene.add_object(plane)

    # Background plane
    background_plane_point = [0.0, 0.0, -100]  # Position far behind the objects
    background_plane_normal = [0, 0, 1]  # Normal pointing towards the camera
    background_plane_color = [135, 206, 235]  # Light blue background (sky-like color)
    background_plane = Plane(background_plane_point, background_plane_normal, background_plane_color)
    scene.add_object(background_plane)
    
    # Add a cylinder
    cylinder_center = [-100, -100, 300]  # Base center of the cylinder
    cylinder_axis = [0, 1, 0]  # Cylinder axis pointing up
    cylinder_radius = 30  # Radius of the cylinder
    cylinder_height = 200  # Height of the cylinder
    cylinder_color = [0, 0, 255]  # Blue cylinder
    cylinder = Cylinder(cylinder_center, cylinder_axis, cylinder_radius, cylinder_height, cylinder_color)
    scene.add_object(cylinder)
    
    # Add multiple light sources with different colors
    # light_position1 = [600, -10, 1050]  # Light position
    # light_intensity1 = 0.6  # Light intensity
    # light_color1 = [255, 255, 255]  # White light
    # light1 = Light(light_position1, light_intensity1, light_color1)
    # scene.add_light(light1)
    
    light_position2 = [-600, 10, 1050]  # Another light position
    light_intensity2 = 1
    light_color2 = [0, 255, 0]  # Green light
    light2 = Light(light_position2, light_intensity2)
    scene.add_light(light2)

    # light_position3 = [0, 500, 500]  # Top light position
    # light_intensity3 = 1
    # light_color3 = [255, 255, 255]  # White light
    # light3 = Light(light_position3, light_intensity3, light_color3)
    # scene.add_light(light3)

    # Render the scene
    image_data = scene.render()
    
    # Save the image
    image = Image.fromarray(image_data, "RGB")
    image.save("rendered_scene.png")
    image.show()

if __name__ == "__main__":
    main()
