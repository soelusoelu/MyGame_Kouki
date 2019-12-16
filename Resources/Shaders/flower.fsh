varying vec4 v_color;
uniform vec2 center;
uniform vec2 size_div2;

void main(){
    vec2 p = gl_FragCoord.xy - center;
    float col = p.x * p.x + p.y * p.y;
    col /= size_div2.x * size_div2.x;
    float angle = atan(p.y, p.x);
    float deg = degrees(angle);
    col += step(abs(deg), 30.0);
    col = 1 - col;
    col = sign(col);
    gl_FragColor = vec4(col, col, 0, 1);
}