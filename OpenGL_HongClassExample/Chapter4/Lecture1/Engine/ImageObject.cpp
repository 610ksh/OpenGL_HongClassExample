#include "ImageObject.h"

// https://learnopengl.com/Getting-started/Textures
// vcpkg install stb:x64-windows
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace jm
{
	// Use tr_r, tr_g, tr_b set transparent color
	// 투명하게 만들고 싶은 색의 rgb를 넣어야 함. 흰색은 (255,255,255) 검은색은 (0,0,0)임
	// 디폴트값은 -1로 되어있어서 적용이 안되도록 만들어 놓음.
	void ImageObject::init(const string & filename, const int tr_r, const int tr_g, const int tr_b)
	{
		glEnable(GL_BLEND); // 알파블렌딩 하겠다는 의미 (불투명도 관련)
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 알파 블렌딩 옵션설정

		int width, height, n_ch;
		//이미지 파일 읽어오기. 해상도를 가져옴, 채널(알파까지 포함하면 4채널, 아니면 3채널 등등), 
		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n_ch, 0); 

		if (data)
		{
			// 4채널, 알파값 포함됐으면
			if (n_ch == 4)
			{
				int count = 0;
				for (int j = 0; j < height; ++j)
					for (int i = 0; i < width; ++i)
					{
						unsigned char & r = data[count];
						unsigned char & g = data[count + 1];
						unsigned char & b = data[count + 2];

						if (r == tr_r && g == tr_g && b == tr_b)
						{
							// 투명도를 높여줌
							data[count + 3] = 0; // alpha = 0 -> transparent
						}

						count += 4;
					}
			}

			//cout << width << " " << height << " " << n_ch << endl;

			// 비율을 저장해놓는 이유 : 컴퓨터 그래픽스에서 텍스쳐를 내부에서 저장할때 정사각형으로 저장하기 때문
			ratio = static_cast<float>(width) / static_cast<float>(height);

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (n_ch == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else if (n_ch == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else
			{
				printf("Use RGB or RGBA images. Your input image has %d channels.", n_ch);
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}
	
	void ImageObject::draw()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		beginTransformation();

		// 1 x 1로 바꾸기 위해 0.5f를 곱해주고, 비율을 바꿔주려고 1.0f * 0.5f로 수정하는것임
		scale(ratio * 0.5f, 1.0f * 0.5f);

		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// 이미지를 그릴때 기본적으로, 가로2 x 세로2인 사각형을 그리고 거기에 덧붙이는 형태임
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);

		// upside down texture coordinates
		glTexCoord2d(0.0f, 1.0f);
		glVertex2d(-1.0f, -1.0f);

		glTexCoord2d(1.0f, 1.0f);
		glVertex2d(1.0f, -1.0f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2d(1.0f, 1.0f);

		glTexCoord2d(0.0f, 0.0f);
		glVertex2d(-1.0f, 1.0f);

		/*glTexCoord2d(0.0f, 0.0f);
		glVertex2d(-1.0f, -1.0f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2d(1.0f, -1.0f);

		glTexCoord2d(1.0f, 1.0f);
		glVertex2d(1.0f, 1.0f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2d(-1.0f, 1.0f);*/

		glEnd();

		endTransformation();

		glDisable(GL_TEXTURE_2D);
	}
}
