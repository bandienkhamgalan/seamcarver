#version 150

out vec4 fragColor;

uniform int screenWidth;
uniform int screenHeight;
uniform int imageRowPitch;
uniform int imageWidth;
uniform int imageHeight;

uniform usamplerBuffer image;

void main()
{
	int row = int((1 - gl_FragCoord.y / screenHeight) * imageHeight);
	int col = int(gl_FragCoord.x / screenWidth * imageWidth);
	uvec4 texelColor = texelFetch(image, col + imageRowPitch * row);
	fragColor = vec4(texelColor.rgb / 255.0f, 1.0f);
}
