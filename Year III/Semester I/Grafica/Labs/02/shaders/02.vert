//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;

#version 330    //  Versiunea GLSL;

//  Variabile de intrare (dinspre programul principal);
layout (location = 0) in vec4 in_Position;     //  Se preia din buffer de pe prima pozitie (0) atributul care contine coordonatele;
layout (location = 1) in vec4 in_Color;        //  Se preia din buffer de pe a doua pozitie (1) atributul care contine culoarea;

//  Variabile de iesire;
out vec4 gl_Position;   //  Transmite pozitia actualizata spre programul principal (nemodificata in acest exemplu);
out vec4 ex_Color;      //  Transmite culoarea (de modificat in Shader.frag); 

uniform float theta;

void main(void)
{
    float s = sin(theta);
    float c = cos(theta);

    gl_Position = in_Position;
    gl_Position[0] = in_Position[0] * c - in_Position[2] * s;
    gl_Position[2] = in_Position[0] * s + in_Position[2] * c;
    ex_Color = in_Color;
}