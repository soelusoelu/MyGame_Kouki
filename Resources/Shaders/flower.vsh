attribute vec4 a_position;
attribute vec4 a_color;
uniform mat4 u_wvp_matrix;

varying vec4 v_color;

void main() {
    gl_Position = u_wvp_matrix * a_position;
    v_color = a_color;
}