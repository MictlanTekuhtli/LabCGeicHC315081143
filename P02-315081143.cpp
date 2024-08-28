//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;

std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//shaders nuevos se crear�an ac�
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* fShaderRojo = "shaders/shaderRojo.frag";
static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* fShaderAzul = "shaders/shaderAzul.frag";
static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* fShaderCafe = "shaders/shaderCafe.frag";
static const char* vShaderVerdeClaro = "shaders/shaderVerdeClaro.vert";
static const char* fShaderVerdeClaro = "shaders/shaderVerdeClaro.frag";
static const char* vShaderVerdeOscuro = "shaders/shaderVerdeOscuro.vert";
static const char* fShaderVerdeOscuro = "shaders/shaderVerdeOscuro.frag";

float angulo = 0.0f;

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
		//X		  Y		 Z			R		G		B
		-0.7f,	0.9f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.9f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.9f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.6f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.6f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.6f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.1f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.7f,	0.1f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.1f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.1f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.3f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.9f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.4f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.7f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.3f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.2f,	0.6f,	0.0f,		0.0f,	0.0f,	1.0f,
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,330);
	meshColorList.push_back(letras);

	GLfloat vertices_letras2[] = {
		//X		 Y		 Z			R		G		B
		0.4f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.5f,	0.9f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.5f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.5f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.7f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.2f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.1f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.2f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.1f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.4f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.3f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.8f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.7f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.9f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.6f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.8f,	0.3f,	0.0f,		1.0f,	0.0f,	0.0f,
		0.9f,	0.1f,	0.0f,		1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* letras2 = new MeshColor();
	letras2->CreateMeshColor(vertices_letras2, 234);
	meshColorList.push_back(letras2);

	GLfloat vertices_letras3[] = {
		//X		 Y		 Z			R		G		B
		-0.1f,	-0.1f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.1f,	-0.1f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.1f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.1f,	-0.1f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.9f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.1f,	-0.9f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.9f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.4f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		-0.1f,	-0.9f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.4f,	-0.7f,	0.0f,		0.0f,	1.0f,	0.0f,
		0.4f,	-0.9f,	0.0f,		0.0f,	1.0f,	0.0f,

	};

	MeshColor* letras3 = new MeshColor();
	letras3->CreateMeshColor(vertices_letras3, 90);
	meshColorList.push_back(letras3);

}

void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//se agregan los nuevos shader aqui
	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo); //Shader Rojo
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderAzul, fShaderAzul); //Shader Azul
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderCafe, fShaderCafe); //Shader Cafe
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vShaderVerdeClaro, fShaderVerdeClaro); //Shader Verde Claro
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro); //Shader Verde Oscuro
	shaderList.push_back(*shader7);

}

int main()
{
	mainWindow = Window(700, 700);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		/*
		//2D										
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		//Letra 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, -0.1f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		
		//Letra 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//Letra 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();
		*/

		//3D
		//Piramide azul
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.1;

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, -1.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 1.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//Piramide azul

		//Cubo rojo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubos verdes
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -1.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, -0.2f, -1.6f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, -0.2f, -1.6f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//Cubos cafes
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.85f, -0.85f, -1.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.85f, -0.85f, -1.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//Piramides verdes oscuros
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.85f, -0.42f, -1.6f));
		model = glm::scale(model, glm::vec3(0.5f, 0.8f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.85f, -0.42f, -1.6f));
		model = glm::scale(model, glm::vec3(0.5f, 0.8f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/