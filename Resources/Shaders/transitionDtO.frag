uniform sampler2D texture;
uniform bool expand;
uniform float time;
uniform float maxTime;
uniform vec2 pos;
uniform float maxx;


void main()
{
    float delta;
    if (expand) delta = (time/maxTime);
    else delta = 1.0-(time/maxTime);
    vec2 pix = gl_FragCoord.st;
    float distx = (pos.x - pix.x)*(pos.x - pix.x);
    float disty = (pos.y-pix.y)*(pos.y-pix.y);
    float aux = distx + disty;
    float distancee = sqrt(aux);
    float posDelta = (distancee/maxx);
    //if (posDelta > 1.0) gl_FragColor = vec4(delta,delta,delta,1);

    if (delta < posDelta) gl_FragColor = vec4(posDelta,posDelta,posDelta,1);
    else gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
}