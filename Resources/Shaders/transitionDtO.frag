uniform sampler2D texture;
uniform bool expand;
uniform float time;
uniform float maxTime;
uniform vec2 pos;
uniform float max;


void main()
{
    float delta;
    if (expand) delta = (time/maxTime);
    else delta = 1.0-(time/maxTime);
    vec2 pix = gl_FragCoord.st;
    float distance = sqrt(pow(pos.x - pix.x,2)+pow(pos.y-pix.y,2));
    float posDelta = (distance/max);
    //if (posDelta > 1.0) gl_FragColor = vec4(delta,delta,delta,1);

    if (delta < posDelta) gl_FragColor = vec4(posDelta,posDelta,posDelta,1);
    else gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
}