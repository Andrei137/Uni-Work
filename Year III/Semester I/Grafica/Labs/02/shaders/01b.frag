//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;

#version 330	//  Versiunea GLSL;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codColShader;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;
uniform vec4 color4;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
	switch (codColShader)
	{
		case 0:
			out_Color = color1;
			break;

		case 1:
			out_Color = color2;
			break;

		case 2:
			out_Color = color3;
			break;

		case 3:
			out_Color = color4;
			break;

		default:
			out_Color = ex_Color;
	}
}
