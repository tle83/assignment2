#include <stdlib.h>
#include <math.h>

#include <sys/types.h>
#include <gl/glut.h>

#include <iostream>
#include <fstream>

using namespace std;

class Vertex
{
public:
	double x, y, z;

	Vertex(double x, double y, double z);
	void setCoordinates(double xval, double yval, double zval);
};

class Normal
{
public:
	double x, y, z;

	Normal(double x, double y, double z);
	void setCoordinates(double xval, double yval, double zval);
};

class Texel
{
public:
	double u, v;

	Texel(double u, double v);
	void setCoordinates(double uval, double vval);
};

class Face
{
public:
	int *vList;
	int *nList;
	int *tList;
	int vIndex;
	const int DEFAULT_SIZE;
	int current_max_size;

	Face();
	void addVertex(int v);
	void addVertexTexel(int v, int t);
	void addVertexNormal(int v, int n);
	void addVertexNormalTexel(int v, int n, int t);
private:
	void add(int v, int n, int t);


};


class WavefrontObj
{
public:
	Vertex **v;
	int vIndex;
	int current_max_verticies;

	Normal **n;
	int nIndex;
	int current_max_normals;

	Texel **t;
	int tIndex;
	int current_max_texels;

	Face **f;
	int fIndex;
	int current_max_faces;

	bool isFlat;
	GLuint mode;

	WavefrontObj(char *filename);

	void addVertex(double x, double y, double z);
	void addVertex(Vertex *vert);
	void addNormal(double x, double y, double z);
	void addNormal(Normal *norm);
	void addTexel(double u, double v);
	void addTexel(Texel *texl);
	Face *addFace();
	Normal *faceNormal(Vertex *v0, Vertex *v1, Vertex *v2);
	void Draw();
private:
	const int DEFAULT_SIZE;
};

