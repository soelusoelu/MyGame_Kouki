varying vec4 v_color;
uniform vec2 center;
uniform vec2 size_div2;

void main(){
    vec2 p = gl_FragCoord.xy - center;
    float col = p.x * p.x + p.y * p.y;
    col /= size_div2.x * size_div2.x;
    col = 1 - col;
    gl_FragColor = vec4(col, col, col, 1);
}