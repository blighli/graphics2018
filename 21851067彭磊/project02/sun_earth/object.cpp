#include"object.h"

Object::Object(const char* path)
{
	FILE *file;
	fopen_s(&file, path, "rb");
	if (!file)
	{
		std::cout << "read obj file fail" << std::endl;
	}
	char line[1024];
	std::vector<vec3> tempNors;
	std::vector<vec2> tempTex;
	while (!feof(file))
	{
		fgets(line, 1024, file);
		std::vector<string> parts;

		std::string strLine = line;
		std::string endMark = " ";
		std::string ans = "";
		strLine = strLine.append(endMark);
		for (int i = 0; i < strLine.size(); i++)
		{
			if (strLine[i] != ' ')
				ans += strLine[i];
			else
			{
				parts.push_back(ans);
				ans = "";
			}
		}
		if (parts[0] == "v")
		{
			Vertex vertex;
			vertex.Position = vec3 ( (float)atof(parts[1].c_str()), (float)atof(parts[2].c_str()), (float)atof(parts[3].c_str()));
			vertices.push_back(vertex);
		}
		if (parts[0] == "vn")
		{
			hasNormal = true;
			vec3 normal((float)atof(parts[1].c_str()), (float)atof(parts[2].c_str()), (float)atof(parts[3].c_str()));
			tempNors.push_back(normal);
		}
		if (parts[0] == "vt")
		{
			hasTex = true;
			vec2 textCood((float)atof(parts[1].c_str()), (float)atof(parts[2].c_str()));
			tempTex.push_back(textCood);
		}
		if (parts[0] == "f")
		{
			unsigned short indexs[4];                      //位置序号
			int tempTexts[4] = { 0 };                      //材质对应序号
			int tempNormals[4] = { 0 };                    //法向量对应序号
			if (!hasTex && !hasNormal)
			{
				for (int i = 1; i < 4; i++)
				{
					indexs[i] =(unsigned short) atof(parts[i].c_str()) - 1;
				}
			}
			else
			{
				for (int i = 1; i < 4; i++)
				{
					string s = parts[i];
					string ans1 = "";
					int sw = 1;
					for (int j = 0; j < s.size(); j++)
					{

						if (s[j] != '/')
						{
							ans1 += s[j];
						}
						else
						{
							if (ans1 != "")
							{
								if (sw == 1)
									indexs[i] = (unsigned short)atof(ans1.c_str()) - 1;
								else if (sw == 2)
								{
									tempTexts[i] = (int)atof(ans1.c_str()) - 1;
								}

							}
							else
							{
								if (sw == 2)
									--tempTexts[i];
							}
							sw++;
							ans1 = "";
						}
					}
					if (ans1 != "")
						tempNormals[i] = (int)atof(ans1.c_str()) - 1;
					else
					{
						--tempNormals[i];
					}
				}
				for (int i = 1; i < 4; i++)
				{
					if (tempNormals[i] != -1)
						vertices[indexs[i]].Normal = tempNors[tempNormals[i]];
					if (tempTexts[i] != -1)
						vertices[indexs[i]].TexCoords = tempTex[tempTexts[i]];
				}
			}


			

			indices.push_back(vec3u(indexs[1], indexs[2], indexs[3]));
		}
	}

}