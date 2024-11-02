#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>


// Function to check if a ray hits a sphere
double hit_sphere(const point3& center, double radius, const ray& r) {
    // Vector from the ray origin to the center of the sphere
    vec3 oc = center - r.origin();

    // Calculate the values for the quadratic formula
    auto a = dot(r.direction(), r.direction()); // The direction squared (part of distance measurement)
    auto b = -2.0 * dot(r.direction(), oc);     // Twice the direction and distance product
    auto c = dot(oc, oc) - radius * radius;     // Distance squared minus the sphere's radius squared

    // Calculate the discriminant to determine if the ray hits the sphere
    auto discriminant = b * b - 4 * a * c;

    // If discriminant is negative, the ray misses the sphere (no real solution)
    if (discriminant < 0) {
        return -1.0;
    } else {
        // Return the closest hit point along the ray
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

// Function to compute the color of a ray, checking if it hits a sphere or returns background color
color ray_color(const ray& r) {
    // Check if the ray hits a sphere at position (0, 0, -1) with a radius of 0.5
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    
    // If t > 0, we have a hit (positive t means the hit is in front of the ray origin)
    if (t > 0.0) {
        // Calculate the normal vector at the hit point on the sphere's surface
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1)); // Normalized vector from sphere center to hit point

        // Map normal vector to a color value, adjusting to range 0 to 1 for RGB display
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    // If no hit, calculate background gradient color based on ray direction
    vec3 unit_direction = unit_vector(r.direction()); // Normalize ray direction
    auto a = 0.5 * (unit_direction.y() + 1.0);        // Scale y direction for smooth gradient

    // Interpolate between white (top) and light blue (bottom) based on direction
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
