uniform sampler2D texture;
uniform float maxTime;
uniform vec2 posLight;
uniform float max;
uniform float min;


void main()
{
    vec2 pix = gl_FragCoord.st;
    float distance = sqrt(pow(posLight.x - pix.x,2)+pow(posLight.y-pix.y,2));
    float delta = max(1.0-((distance - min) / (max - min)),0.1);
    if (distance > max) gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * vec4(0.1,0.1,0.1,1) * gl_Color;
    else if (distance < min) gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
    else gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * vec4(delta,delta,delta,1.0);
    //if (delta < posDelta) gl_FragColor = vec4(posDelta,posDelta,posDelta,1);
     
}