#version 120

varying float intensity;
uniform vec4 color;

void main()
{
    vec4 newcolor;
    
    if (intensity > 0.95)
        newcolor = vec4(1.0, 0.5, 0.5, 1.0) * color;
    else if (intensity > 0.5)
        newcolor = vec4(0.6, 0.3, 0.3, 1.0) * color;
    else if (intensity > 0.25)
        newcolor = vec4(0.4, 0.2, 0.2, 1.0) * color;
    else
        newcolor = vec4(0.2, 0.1, 0.1, 1.0) * color;
    
    newcolor = normalize(newcolor);

    gl_FragColor = newcolor;
}