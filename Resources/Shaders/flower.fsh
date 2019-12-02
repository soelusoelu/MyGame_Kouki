varying vec4 v_color;
uniform vec2 center;
uniform vec2 size_div2;

void main(){
    vec2 p = gl_FragCoord.xy - center;
    p.x /= size_div2.x / 2;
    float col = p.x;
    gl_FragColor = vec4(col, col, col, 1);
}