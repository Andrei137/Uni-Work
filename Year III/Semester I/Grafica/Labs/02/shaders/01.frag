//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;

#version 330	//  Versiunea GLSL;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codColShader;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
	switch (codColShader)
	{
		case 0:
			out_Color = vec4 (1.0, 1.0, 0.0, 0.0) * 0.9;
			break;
		case 1:
			out_Color = vec4 (0.0, 1.0, 1.0, 0.0);
			break;
		default:
			out_Color = vec4 (1.0, 0.0, 1.0, 0.0);
	}
}
