/*
A very basic, very broken raymarcher
Yields a black sphere on a white background but does so in a pretty broken way, space folding doesn't work as it should
*/

#include <math.h>
#include <stdio.h>

#define WIDTH  512
#define HEIGHT 512

typedef struct {
	float x;
	float y;
	float z;
} v3;

typedef struct {
	float x;
	float y;
} v2;

v3 v3add(v3 a, v3 b) { return (v3){a.x + b.x, a.y + b.y, a.z + b.z}; }
v3 v3sub(v3 a, v3 b) { return (v3){a.x - b.x, a.y - b.y, a.z - b.z}; }
v3 v3mul(v3 a, v3 b) { return (v3){a.x * b.x, a.y * b.y, a.z * b.z}; }
v3 v3mulf(v3 a, float b) { return (v3){a.x * b, a.y * b, a.z * b}; }
v3 v3div(v3 a, v3 b) { return (v3){a.x / b.x, a.y / b.y, a.z / b.z}; }
v3 v3abs(v3 a) { return (v3){fabs(a.x), fabs(a.y), fabs(a.z)}; }
double v3len(v3 a) { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
v3 v3norm(v3 a)
{
	double len = v3len(a);
	return (v3){a.x / len, a.y / len, a.z / len};
}

v3 v3rep(v3 a, float b)
{
	v3 c = {
		fmod(a.x + b * .5, b) - b * .5,
		fmod(a.y + b * .5, b) - b * .5,
		fmod(a.z + b * .5, b) - b * .5,
	};
	return c;
}

float scene(v3 p) { return v3len(p) - .5; }

v3 image(v2 uv)
{
	v3 col, ro = {0, 1, -10}, rd = v3norm((v3){uv.x - .5, uv.y - .5, 1});

	float t = 0;
	int i;
	for (i = 0; i < 100; i++) {
		v3 p = v3add(ro, v3mulf(rd, t));
		float d = scene(p);
		t += d;
		if (d < 0.01 || t > 100) break;
	}

	v3 p = v3add(ro, v3mulf(rd, t));
	float d = scene(p);

	if (d < 0.01) {
		col = (v3){0, 0, 0};
	} else {
		col = (v3){1, 1, 1};
	}

	return col;
}

void main()
{
	printf("P3 ");
	printf("%d %d ", WIDTH, HEIGHT);
	printf("255\n");

	for (int y = 0; y < HEIGHT; y++) {

		for (int x = 0; x < WIDTH; x++) {
			v2 uv = {(float)x / WIDTH, (float)y / HEIGHT};
			v3 col = image(uv);
			printf("%d %d %d ", (int)floor(col.x * 255.99), (int)floor(col.y * 255.99), (int)floor(col.z * 255.99));
		}

		printf("\n");
	}
}
