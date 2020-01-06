varying vec4 v_color;
uniform vec2 center;
uniform vec2 size_div2;
uniform float time;

void main(){
    float col = 1.0;
    vec2 p = gl_FragCoord.xy - center;

    col = p.x * p.x + p.y * p.y;
    col /= size_div2.x * size_div2.x;
    float w = sin(time * 3.14) + 0.8;
    col /= w / 2.0 + 0.5;
    col = 1 - col;

    gl_FragColor = vec4(col, col, col, 1);
}