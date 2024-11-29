//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_05_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;
in vec2 tex_Coord;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

// Variabile uniforme
uniform int drawOption;
uniform sampler2D myTexture;

// Variabile pentru culori
vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
vec4 white = vec4(1.0, 1.0, 1.0, 1.0);

void main(void)
{
	switch (drawOption)
	{
		case 0:
			out_Color = ex_Color; // patratul initial
			break;
		case 1:
			out_Color = mix(red,green,0.9); // intai scalare, apoi translatie
			break;
		case 2:
			out_Color = texture(myTexture, tex_Coord);   // intai translatie, apoi scalare
			break;
	}
}
