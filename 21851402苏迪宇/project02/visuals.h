struct point
{
	float x;
	float y;
	float z;
};

struct face
{
	int vtx[3];
	int vtn[3];
};

struct normal
{
	float x;
	float y;
	float z;
};

struct model
{
	point obj_points[9122];
	normal obj_normalls[9124];
	face obj_faces[18240];
	int vertices;
	int faces;
	int normalls;
};

void Render();
void Resize(int w, int h);
void Setup();
void ReadFile(model *md);
void DisplayModel(model md);
void Idle();
void Keyboard(unsigned char key, int x, int y);
void CreatePlanet(int colour);
void star(float transun);

void pinakas();
void stars(float transun);
