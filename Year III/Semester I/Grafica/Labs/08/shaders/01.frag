//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laborator VIII - 08_01_Shader.frag       |
// ===========================================
//
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330

float winWidth = 1400; // Latimea ferestrei

//  Variabile de intrare (dinspre Shader.vert);
in vec4 gl_FragCoord; // Variabila care indica pozitia fragmentului (prin raportare la fereastra de vizualizare)
in vec3 ex_Color;

//  Variabile de iesire (spre programul principal);
out vec3 out_Color;

//  Variabile uniforme;
uniform int codCol;

void main(void)
{
    switch (codCol)
    {
        case 1:
            out_Color=vec3(0.0, 0.0, 0.0);
            break;
        case 2:
            // Sun
            out_Color = vec3(1.0 - gl_FragCoord.x / winWidth, 1.0 - gl_FragCoord.x / winWidth, 0.0);
            break;
        case 3:
            // Earth
            out_Color=vec3(0.0, 0.0, 1.0 - gl_FragCoord.x/winWidth);
            break;
        case 4:
            // Moon
            out_Color=vec3(1.0 - gl_FragCoord.x/winWidth, 0.0, 0.0);
            break;
        default:
            out_Color=ex_Color;
    }
}
