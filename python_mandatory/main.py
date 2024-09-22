# main.py
from PIL import Image
from objects import Ray, Sphere, Light, Scene, Camera, Plane, Cylinder  # Import Plane class

def main():
    width, height = 800, 600
    fov = 90
    camera_position = [0, 0, 500]
    camera_direction = [0, 0, -1]  # Looking along the positive x-axis

    camera = Camera(camera_position, camera_direction, fov)
    scene = Scene(camera, width, height)
    
    # Add sphere from the .rt description
    # sphere_center = [0.0, 0.0, 200]
    # sphere_radius = 100 / 2.0  # Corrected sphere radius
    # sphere_color = [255, 0, 0]
    # sphere = Sphere(sphere_center, sphere_radius, sphere_color)
    # scene.add_object(sphere)

    cylinder_center = [0, 0, 300]  # Base center of the cylinder
    cylinder_axis = [0, 1, 0]  # Cylinder axis pointing up
    cylinder_radius = 30  # Radius of the cylinder
    cylinder_height = 200  # Height of the cylinder
    cylinder_color = [0, 0, 255]  # Blue cylinder
    cylinder = Cylinder(cylinder_center, cylinder_axis, cylinder_radius, cylinder_height, cylinder_color)
    scene.add_object(cylinder)
    
    # Add a plane with the given description
    plane_point = [0.0, -210.0, 0]
    plane_normal = [0, 1, 0]
    plane_color = [255, 255, 255]
    plane = Plane(plane_point, plane_normal, plane_color)
    scene.add_object(plane)
    
    # Add a light source
    # light_position = [600, -10, 1050]
    # light_intensity = 0.6
    # light = Light(light_position, light_intensity)
    # scene.add_light(light)
    
    light_position2 = [-600, 10, 1050]
    light_intensity2 = 0.6
    light2 = Light(light_position2, light_intensity2)
    scene.add_light(light2)

    # Render the scene
    image_data = scene.render()
    
    # Save the image
    image = Image.fromarray(image_data, "RGB")
    image.save("rendered_scene.png")
    image.show()

if __name__ == "__main__":
    main()
