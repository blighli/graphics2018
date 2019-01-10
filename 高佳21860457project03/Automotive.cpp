//ԭʼ���ߣ���۾����ṩ�˳���˼·�����׵��˶�����
//�޸��ߣ������������޸����й��ܣ���ƥ��AutoPart��

#include "Automotive.h"

myCar::myCar(void)
{
	this->normal3f	  = CVertex(0,1,0);
	this->position    = CVertex(0,0,0);
	this->ready       = 0;
	this->rotx        = 0;
	this->roty        = 0;
	this->rotz        = 0;
	this->wheel       = NULL;
	this->wheel_num   = 0;
	this->viewangle   = 0;
	m_carbody = new AutoPartBody("jeep.3ds");
}

myCar::~myCar(void)
{
}

bool myCar::CreateDemoCar(void)
{
	CVertex * newV;
	CVertex * zeroV;
	CVertex * defV;//��׼��ȷ��
	AutoPartWheel  * newP;
	int i,j;
	newV = NULL;
	newP = NULL;
	i=0;
	j=0;
	/////------------------------------------���ñ�׼ֵ
	double d_w1_2 = 1.0;////�����־��һ��
	double d_w2_2 = 1.6;////ǰ���־��һ��---------���һ��

	zeroV = new CVertex(0,0,0);
	defV = new CVertex(32,32,0);
	////////////////////ԭ��
	this->Setpos(* zeroV);
	///////////////////����

	this->CreateDemo4Wheel(d_w1_2, d_w2_2);
	m_carbody->DrawGL();
	this->ready=1;
	return true;
}

bool myCar::CreateWheel(int n)
{
	if (n>0)
	{
		if (this->wheel=new AutoPartWheel[n])
		{
			this->wheel_num = n;
			return true;
		}
	}
	return false;
}

bool myCar::Setpos(CVertex p)
{
	this->position = p;
	return false;
}

bool myCar::SetOri(CVertex ori)
{
	this->normal3f = ori;
	return false;
}

bool myCar::Rotxyz(double x, double y, double z)
{
	this->rotx += x;
	this->roty += y;
	this->rotz += z;
	while (rotz>360)    rotz -= 360;
	while (rotz<-360)   rotz += 360;
	return false;
}

bool myCar::ResetRot(void)
{
	this->rotx=0;
	this->roty=0;
	this->rotz=0;
	return false;
}

bool myCar::CreateDemo4Wheel(double dx, double dy)
{
	CVertex * newV;
	CVertex * newV2;
	CVertex * zeroV;
	CVertex * maxV;
	CVertex * defV;//��׼��ȷ��
	AutoPartWheel  * newP;
//	double ds2;
	int i,j;
	newV=NULL;
	newV2=NULL;
	newP=NULL;
	i=0;
	j=0;
	zeroV = new CVertex(0,0,0);
	maxV = new CVertex(1,1,1);
	defV = new CVertex(32,32,0);
//	ds2=ds/2;
	double r=0;
	double xx=0;
	double h1=0;
	double h2=0;
//		xx=ds/2 + 0.005;//���
//		r=dz/2;//���ǰ뾶�뾶
//		h1=r/2;
//		h2=sqrt(3.0)*h1;

	/////-----------------
	this->CreateWheel(4);


	newV = new CVertex(-dx, dy,0);
	this->wheel[0].Set(* newV);
	this->wheel[0].rotable=1;
	newV = new CVertex( dx, dy,0);
	this->wheel[1].Set(* newV);
	this->wheel[1].rotable=1;
	newV = new CVertex(-dx,-dy,0);
	this->wheel[2].Set(* newV);
	newV = new CVertex( dx,-dy,0);
	this->wheel[3].Set(* newV);
	return false;
}

bool myCar::DrawGL(void)
{
	int i=0;
	double rott=0;//////////����ƫ�򣬾����ĳ���ƫ�����
	double ws=0;///////////�����ٶȾ���
	if (this->ready == 1)
	{
		glPushMatrix();

		glEnable(GL_DEPTH_TEST); //
		glDisable(GL_BLEND); // �رջ��
		////-------------
		if (this->viewangle==0)////viewangle�����ӽ�
		{
			glTranslatef(position.x,position.y,position.z);
			if (rotz>360) rotz-=360;
			if (rotz<0) rotz+=360;
			glRotatef(rotx,1.0f,0.0f,0.0f);
			glRotatef(roty,0.0f,1.0f,0.0f);
			glRotatef(rotz,0.0f,0.0f,1.0f);
		}
		else if (this->viewangle==3)
		{
			////////////-----------------------���ƶ�Ч����ֻ����תЧ��
			glRotatef(0,  1.0f,0.0f,0.0f);
			glRotatef(0,  0.0f,1.0f,0.0f);
			//////////////----------------------����ƫ��Ч��������ƫ��ͳ���ǰ���ٶȾ���
			rott = this->wheel[0].rotz/2;
			ws   = this->wheel[0].speed;////
			rott = rott*ws/50;
			glRotatef(rott,0.0f,0.0f,1.0f);
		}
		m_carbody->DrawGL();
		for (i=0;i<this->wheel_num;++i)
		{
			//////////-------------------������ƫ�򴫸�����
			if (this->viewangle==3)
			{				
				this->wheel[i].rot_fa.z=rott;
			}
			this->wheel[i].DrawGL();
		}
		glPopMatrix();
	}
	return true;
}

bool myCar::MoveVector(CVertex v)//��ĳ�������ƶ�һ������//ֻ�ı䳵ԭ��
{
	this->position = this->position + v;
	return false;
}

bool myCar::WheelAllRot(double wrs, double wori)
{
	int i;
	for (i=0;i<this->wheel_num;++i)
	{
		this->wheel[i].distance -= wrs;/////���������෴�����Լ�ȥ
		this->wheel[i].speed = wrs;////����
		this->wheel[i].rotz = wori;/////��Χ�����ڴ���֮ǰ
		///////------------------��Χ����
		while (this->wheel[i].rotx>360)
		{
			this->wheel[i].rotx -= 360;
		}
		while (this->wheel[i].rotx<0)
		{
			this->wheel[i].rotx += 360;
		}
	}
	return false;
}

void myCar::MovingCalc(double * wrs, double * wori, myCar * car)//////�����ɹ�ʽ�ṩ������ݣ�ֱ���ƶ�,������Ϊ��������
{
	double speed;
	double pi=3.1415926;
	if ((* wrs == 0)&&(* wori==0)) return;//���κα仯
	speed = pi*(* wrs)/180;//ǰ����
	speed = speed/1.15;              //�ٶ�����,�����ӿ���������---------->��Ҫʱ�������ӷ����복�ķ����

	//////////////----------------------������ת����
	double x,y,z;
	double xx,yy,zz;
	double rx,ry,rz;
	/////////////-----------------------��ȡ��������
	x = car->normal3f.x;
	y = car->normal3f.y;
	z = car->normal3f.z;
	/////////�Գ���������ǰ������--------------������Rת����ƫ��
	double wrot = (*wori)*pi/180/3;
	xx=x*cos(wrot)-y*sin(wrot);
	yy=x*sin(wrot)+y*cos(wrot);
	x=xx;
	y=yy;
	////////////------------------------����õ�����ʵ��ǰ������
	rx= car->rotx;
	ry= car->roty;
	rz= car->rotz;
	////-------��zת
	double rtz=rz*pi/180;
	xx=x*cos(rtz)-y*sin(rtz);
	yy=x*sin(rtz)+y*cos(rtz);
	x=xx;
	y=yy;
	////---------x
	double rtx=rx*pi/180;
	yy=y*cos(rtx)-z*sin(rtx);
	zz=y*sin(rtx)+z*cos(rtx);
	y=yy;
	z=zz;
	/////---------y
	double rty=ry*pi/180;
	xx=x*cos(rty)+z*sin(rty);
	zz=-x*sin(rty)+z*cos(rty);
	x=xx;
	z=zz;
	/////////-------------xyzΪ�µķ���ʸ��
	/////////----------------�õ�ǰ��ʸ��
	x=x*speed;
	y=y*speed;
	z=z*speed;
	////////-----------------------------------��������λ��
	car->MoveVector(CVertex(x,y,z));
	///////------------------------------------�������ķ���
	if (fabs(*wrs)>2)
	{
		car->Rotxyz(0,0,(*wori)*(*wrs)/600);
	}
	///////////------------------��������
	car->WheelAllRot(* wrs,* wori);
	///////////////----------------------------�ٶȣ����򣬻ص�
	if (*wrs>0)
	{
		* wrs = (* wrs)*0.98 - 0.001;////3�ɵ���Ħ��������
		if (* wrs < 0) 
		{
			(*wrs)=0;
		}
	}
	else if (*wrs<0)
	{
		* wrs =(* wrs)*0.95 + 0.01;////
		if (*wrs > 0)
		{
			(*wrs)= 0;
		}
	}
	if (*wori < 0)
	{
		*wori = (*wori)*0.98 + 0.2;
		if (*wori>0)
		{
			*wori=0;
		}
	}
	else if (*wori > 0)
	{
		*wori = (*wori)*0.98 - 0.2;
		if (*wori<0)
		{
			*wori=0;
		}
	}
}