#include "Texture.h"

Texture::Texture(){}

//�������� � ������������� ����������� �������
void Texture::load(std::string filename) {
	// ������� ����� "�����������"
	ILuint imageID = ilGenImage();
	// ������ ������� "�����������"
	ilBindImage(imageID);
	// ��������� �����������
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	if (ilLoadImage(unicodeString))
		std::cout <<std::endl<< filename<<"\nTexture open OK\n";
	else std::cout << "Texture open ERROR\n";

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int	height = ilGetInteger(IL_IMAGE_HEIGHT);
	int	format = ilGetInteger(IL_IMAGE_FORMAT);
	int type = ilGetInteger(IL_IMAGE_TYPE);

	std::cout <<"W:"<< width<<std::endl <<"H: " << height << std::endl<<
		"Format: " << format <<std:: endl<<"Type: " << type << std::endl;

	//��������� �� ������� ������, � ������� ����� ������� ������ ��������.
	char* pixels = new char[width * height * 4];
	//C���������� ������ �������� �� ���������� ������ ���������� DevIL � ��������� ������
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, pixels);

	// ���������� ������ ������ (��������� ����������)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);

	//�������� ����������� ������� (1-���������� �������), texIndex - ��������� �� ������ ������� �������
	glGenTextures(1, &texIndex);

	//�������� ����������� ������� (texIndex) � ����������� ����� (GL_TEXTURE_2D)
	glBindTexture(GL_TEXTURE_2D, texIndex);

	//�������� ����������� �� ����������� ������ � ���������� ������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	delete[] pixels;

	//��������� mipmap���.
	glGenerateMipmap(GL_TEXTURE_2D);
	//��������� ���������� ��������.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::apply(TextureFilter texFilter) {
	glBindTexture(GL_TEXTURE_2D, texIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	switch (texFilter)
	{
	case TextureFilter::POINT: {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}
	case TextureFilter::BILINEAR: {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	}
	case TextureFilter::TRILINEAR: {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}
	case TextureFilter::ANISOTROPIC: {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}
	default:
		break;
	}

}

void Texture::disableAll() {
	glBindTexture(GL_TEXTURE_2D, 0);
}