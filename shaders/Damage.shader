shader_type canvas_item;
uniform float highlight;

void fragment()
{
	vec4 pixel = texture(TEXTURE, UV);
	if (pixel.a == 0.0f)
	{
		discard;
	}
	
	COLOR = vec4(texture(TEXTURE, UV).rgb + (highlight) / 2.0f, 1.0f - highlight);
}