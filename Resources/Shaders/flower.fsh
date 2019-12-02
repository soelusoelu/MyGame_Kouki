varying vec4 v_color;

void main(){
    gl_FragColor = vec4(gl_FragCoord.x / 1024, gl_FragCoord.y / 720, 0, 1);
    //gl_FragColor *= v_color;
}