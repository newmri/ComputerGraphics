#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

/* �삠꺃��궥�㎯꺍�먦긿�뺛궊��궢�ㅳ궨 */
#define SELECTIONS 100

/* �ゃ깣�멥궒��깉��빊 */
#define NOBJECTS 8

/* �뉎궍�밤깤�с궎�ゃ궧�덀겗鈺섇닪耶� */
GLuint objects;

/* �꾠궕�뽧궦�㎯궚�덀겗�� */
GLfloat *color[NOBJECTS];

/* �꿔깈�쇈궭 */
GLfloat gray[] = { 0.7, 0.7, 0.7 };
GLfloat blue[] = { 0.1, 0.1, 0.9 };

void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* 訝��╉궥�쇈꺍�믤룒�삠걲�� */
	for (i = 0; i < NOBJECTS; i++) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color[i]);
		glCallList(objects + i);
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	static GLuint selection[SELECTIONS];  /* �삠꺃��궥�㎯꺍�먦긿�뺛궊���������� */
	static GLint hits = 0;                /* �삠꺃��깉�뺛굦�잆궕�뽧궦�㎯궚�덀겗�� */

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			GLuint *ptr;
			GLint vp[4];
			int i;

			/* �삠꺃��궥�㎯꺍�ヤ슴�녴깘�껁깢�▲겗鼇�츣竊롢걪�뚣겘�삠꺃��궥��
			�녈깴�쇈깋餓ε쨼��셽竊늛lRenderMode(GL_SELECT) �덀굤�랃펹
			�ュ츪烏뚣걲�뗥퓚誤곥걣�귙굥竊롢궩�с궚�룔깾�녈깘�껁깢�▲겓��펽��
			�뗣걽�묆겗�뉎꺖�욍걣屋겹굙渦쇈겲�뚣굥 */
			glSelectBuffer(SELECTIONS, selection);

			/* �с꺍���ゃ꺍�겹깴�쇈깋�믡궩�с궚�룔깾�녈깴�쇈깋�ュ늾�욍걟�� */
			glRenderMode(GL_SELECT);

			/* �삠꺃��궥�㎯꺍�먦긿�뺛궊��닜�잌뙑竊뚣걪�뚣겘�삠꺃��궥�㎯꺍�㏂꺖
			�됥겓�ゃ겂�╉겒�꾠겏�↑쫿�뺛굦�� */
			glInitNames();

			/* �띲꺖�졼궧�욍긿��겗�덆젺�ヤ뺍��릫�띲굮屋겹굙�╉걡�륅펿�띲꺖��
			�밤궭�껁궚�や퐪��쨭�겹겗�ゃ깣�멥궒��깉�뚪겦�욁겎�띲굥�덀걝��
			�밤궭�껁궚礪뗩�졼겓�ゃ겂�╉걚�뗣걣竊뚥퍓�욁겘竊묈�뗣겗�ゃ깣�멥궒��
			�덀걮�뗩겦�욁걮�ゃ걚��겎竊뚣깓�쇈깲�밤궭�껁궚��뀍��겗誤곭킔��
			�묆굮�뽧굤�욍걟�ゃ걣�됪룒�삠걲�뚣겙�덀걚竊롢걹�볝겎竊뚣걗�됥걢��
			�곥깓�쇈깲�밤궭�껁궚��뀍��겓餓�겗�띶뎺 (-1) �ヨŉ�곥겍�듽걚
			��펽�앫걪�믢슴�꾢썮�숋펿 */
			glPushName(-1);

			/* �삠꺃��궥�㎯꺍��눇�녴겘誤뽫궧佯㎪쮽楹삠겎烏뚣걝 */
			glMatrixMode(GL_PROJECTION);

			/* �얍쑉���뤺쫿鸚됪룢�욁깉�ゃ궚�밤굮岳앭춼�쇻굥 */
			glPushMatrix();

			/* �뤺쫿鸚됪룢�욁깉�ゃ궚�밤굮�앮쐿�뽧걲�� */
			glLoadIdentity();

			/* �얍쑉��깛�γ꺖�앫꺖�덅Þ若싥굮孃쀣굥 */
			glGetIntegerv(GL_VIEWPORT, vp);

			/* 烏①ㅊ�섇윜�뚣깯�╉궧�앫궎�녈궭��뫅�꿔걽�묆겓�ゃ굥�덀걝�ュ쨯��
			烏뚦닓�믦Þ若싥걲�뗰펿�욁궑�밤겗佯㎪쮽楹삠겘竊뚣궧��꺁�쇈꺍��벨與�
			楹삠겓野얇걮�╊툓訝뗣걣�띹빪�쀣겍�꾠굥��겎竊뚣걹�뚣굮獒쒏��쇻굥 */
			gluPickMatrix(x, vp[3] - y - 1, 1, 1, vp);

			/* �싧만��룒�삠겏�뚣걯�뤺쫿鸚됪룢�욁깉�ゃ궚�밤굮鼇�츣�쇻굥竊롢궑��
			�녈깋��뀲鵝볝굮�볝깷�쇈깮�쇈깉�ャ걮�╉걚�뗣겗�㏆펽�㏂궧�싥궚��
			驪붵겘 vp[2] / vp[3] �㎩풓�됥굦�뗰펿*/
			gluPerspective(45.0, (double)vp[2] / (double)vp[3], 1.0, 100.0);

			/* �㏂깈�ャ깛�γ꺖�욁깉�ゃ궚�밤겓�뉑쎘�덀굥 */
			glMatrixMode(GL_MODELVIEW);

			/* �볝걪�㏛��╉깴�뉎꺂�볝깷�쇈깯�덀꺁��궧�ュ늾�욍걟��펽�볝깷��
			�ㅳ꺍�겼쨯�쎼굜�㏂깈�ゃ꺍�겼쨯�쎼겗鼇�츣�믡걲�뗣겗�졼걣竊뚨쎍��
			�ユ룒�삠걬�뚣걼�녑숱�ュ��쀣겍�삠꺃��궥�㎯꺍�믦죱�ゃ걝�ゃ굢竊�
			�앫겗�귙겓鵝욍겂�잆깴�뉎꺂�볝깷�쇈깯�덀꺁��궧�뚣걹��겲�얌슴��
			�뗰펷��걳竊됵펿�졼걢�됦퍓��빳訝뗣겗��릤 (#if 0 節� #endif)
			�믥쐛�γ걮�╉굚鸚㏛툑鸚ワ펷�졼겏�앫걝竊�*/

#if 0
			/* �㏂깈�ャ깛�γ꺖鸚됪룢烏뚦닓��닜�잌뙑 */
			glLoadIdentity();

			/* 誤뽫궧��Þ若� */
			gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
#endif

			/* �귙걝訝�佯╉궥�쇈꺍�믤룒�삠걲�� */
			for (i = 0; i < NOBJECTS; i++) {
				/* �띲꺖�졼궧�욍긿��겗�덆젺�ャ걪�뚣걢�됪룒�뤵궕�뽧궦�㎯궚�덀겗
				�ゅ뤇�믦Þ若싥걲�� */
				glLoadName(i);
				/* �ゃ깣�멥궒��깉�믤룒�삠걲�뗰펷�삯씊�ャ겘烏①ㅊ�뺛굦�ゃ걚竊�*/
				glCallList(objects + i);
			}

			/* �띲겞�뤺쫿鸚됪룢�욁깉�ゃ궚�밤겓�뉑쎘�덀굥 */
			glMatrixMode(GL_PROJECTION);

			/* �뤺쫿鸚됪룢�욁깉�ゃ궚�밤굮�껁겓�삠걲 */
			glPopMatrix();

			/* �㏂깈�ャ깛�γ꺖�욁깉�ゃ궚�밤겓�삠걲 */
			glMatrixMode(GL_MODELVIEW);

			/* �с꺍���ゃ꺍�겹깴�쇈깋�믣뀇�ユ댗�� */
			hits = glRenderMode(GL_RENDER);

			/* �삠꺃��궥�㎯꺍�먦긿�뺛궊�ャ겘�꾠걦�ㅳ겗�뉎꺖�욍걣�γ겂�╉걚��
			��걢�뤵걢�됥겒�꾠겗�㏆펽�ⓦ굤�귙걟�싧뀍��겗�앫궎�녈궭�믣룚��
			�뷩걮�╉걡�� */
			ptr = selection;

			/* hits �ャ겘�삠꺃��궥�㎯꺍�먦긿�뺛궊�ユ졏榮띲걬�뚣걼�뉎꺖�욍겗��
			�뚦뀯�뗰펿�뉎꺖�욍걣�삠꺃��궥�㎯꺍�먦긿�뺛궊�ュ뀯�듿늾�됥겒��
			�뚣겙 hits < 0 �ⓦ겒�� */
			for (i = 0; i < hits; i++) {
				/* �삠꺃��궥�㎯꺍�먦긿�뺛궊��뀍��겗誤곭킔���곲겦�욁걬�뚣걼��
				�뽧궦�㎯궚�덀겗�� */
				unsigned int j, n = ptr[0];

				/* 泳싥걦竊믡겇��쫨榮졼겘�곲겦�욁걬�뚣걼鵝띸쉰�ョ쉰�묆굥也θ죱�띶��
				���弱뤷�ㅳ겏��鸚㎩�ㅳ굮寧�뤇�ゃ걮�닸빊�㎬〃�쀣걼�귙겗 */
				double near = (double)ptr[1] / (double)0x7fffffff;
				double far = (double)ptr[2] / (double)0x7fffffff;

				/* �삠꺃��궥�㎯꺍�먦긿�뺛궊��폇�ㅷ쎅��쫨榮좑펷曆삣춻竊앾폆竊됥걢
				�됮겦�욁걬�뚣걼�ゃ깣�멥궒��깉��빁�룔걣�γ겂�╉걚�� */
				ptr += 3;
				for (j = 0; j < n; j++) {
					color[*(ptr++)] = blue; /* �ゃ깣�멥궒��깉��돯�믧쓵�ャ걲�� */
				}
			}
		}
		else {
			GLuint *ptr = selection;
			int i;

			/* selection[] ��냵若밤겘�욁궑�밤겗藥╉깭�욍꺍�믡궚�ゃ긿��걮��
			�귙겓�쀣걢鸚됪쎍�뺛굦�ゃ걚��걳�졼걢�됵펽�얇걽餘뗣겂�╉걚�뗣겘�� */
			for (i = 0; i < hits; i++) {
				unsigned int j, n = ptr[0];

				ptr += 3;
				for (j = 0; j < n; j++) {
					color[*(ptr++)] = gray;
				}
			}
		}

		/* �삯씊�믤쎑�띷룢�덀겍�욍굥 */
		glutPostRedisplay();
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int w, int h)
{
	/* �╉궍�녈깋��뀲鵝볝굮�볝깷�쇈깮�쇈깉�ャ걲�� */
	glViewport(0, 0, w, h);

	/* �뤺쫿鸚됪룢烏뚦닓�믦Þ若싥걲�� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);

	/* �㏂깈�ャ깛�γ꺖鸚됪룢烏뚦닓�믤뙁若싥걮�╉걡�� */
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		break;
	default:
		break;
	}
}

void init(void)
{
	int i;

	/* �앮쐿鼇�츣 */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	/* �꾠궕�뽧궦�㎯궚�덀겗�뉎궍�밤깤�с궎�ゃ궧�덀굮鵝쒌굥 */
	objects = glGenLists(NOBJECTS);
	if (objects <= 0) {
		fprintf(stderr, "Can't create so many objects: %d.\n", NOBJECTS);
	}

	/* �꾠궕�뽧궦�㎯궚�덀겗�꿔굮�앮쐿�� */
	for (i = 0; i < NOBJECTS; i++) {
		color[i] = gray;
	}
}

void scene(void)
{
	const GLdouble width = 4.0;
	const GLdouble center = width / 2.0;
	const GLdouble step = width / (NOBJECTS - 1);
	int i;

	/* �삠꺃��궥�㎯꺍���穩▲겓�ゃ굥�ゃ깣�멥궒��깉�믥뵟�먦걮��펽�뉎궍��
	�쀣꺃�ㅳ꺁�밤깉�믢퐳�ｃ겍�듽걦*/
	for (i = 0; i < NOBJECTS; i++) {

		/* �녑숱�믡깈�ｃ궧�쀣꺃�ㅳ꺁�밤깉�ョ쇉�� */
		glNewList(objects + i, GL_COMPILE);

		/* �껁굮�뤵걦 */
		glPushMatrix();
		glTranslated((double)i * step - center, ((i & 1) * 2 - 1) * step, 0.0);
		glutSolidSphere(0.5, 10, 5);
		glPopMatrix();

		glEndList();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	init();
	scene();
	glutMainLoop();
	return 0;
}