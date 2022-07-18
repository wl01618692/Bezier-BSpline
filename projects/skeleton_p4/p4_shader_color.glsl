#version 330 core

// Output data
out vec3 color;
uniform bool original;
uniform bool bezier;

void main()
{
    if (original) {
        // Color for control points
        if (bezier) {
            // Bezier curve color is green
            color = vec3(0, 1, 0);
        } else {
            // B-spline curve color is white
            color = vec3(1, 1, 1);
        }
    } else {
        // Color for actual curve is always red
        color = vec3(1, 0, 0);
    }
}
