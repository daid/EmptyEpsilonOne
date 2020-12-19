[VERTEX]
attribute vec3 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_uv;

uniform mat4 projection_matrix;
uniform mat4 camera_matrix;
uniform mat4 object_matrix;
uniform vec3 object_scale;

varying vec2 v_uv;

void main()
{
    vec4 pos = camera_matrix * object_matrix * vec4(0.0, 0.0, 0.0, 1.0);
    pos.xy += a_vertex.xy;
    gl_Position = projection_matrix * pos;
    v_uv = a_uv.xy;
}

[FRAGMENT]
uniform sampler2D texture_map;
uniform vec4 color;

varying vec2 v_uv;

void main()
{
    gl_FragColor = texture2D(texture_map, v_uv) * color;
    if (gl_FragColor.a == 0.0)
        discard;
}
