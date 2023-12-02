#include "Texture.h"

//Создание и инициализация текстурного объекта
void Texture::load(std::string filename) {
	// создаем новое "изображение"
	ILuint imageID = ilGenImage();
	// задаем текущее "изображение"
	ilBindImage(imageID);
	// загружаем изображение
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	if (ilLoadImage(unicodeString))
		std::cout << "Texture open OK\n";
	else std::cout << "Texture open ERROR\n";

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int	height = ilGetInteger(IL_IMAGE_HEIGHT);
	int	format = ilGetInteger(IL_IMAGE_FORMAT);
	int type = ilGetInteger(IL_IMAGE_TYPE);

	std::cout <<"W:"<< width<<std::endl <<"H: " << height << std::endl<<
		"Format: " << format <<std:: endl<<"Type: " << type << std::endl;

	//Указатель на область памяти, в которую будет записан массив пикселей.
	char* pixels = new char[width * height * 4];
	//Cкопировать массив пикселей из внутренней памяти библиотеки DevIL в указанный массив
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, pixels);

	// определяем модель памяти (параметры распаковки)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);

	//Создание текстурного объекта (1-количество текстур), texIndex - указатель на первый элемент массива
	glGenTextures(1, &texIndex);

	//Привязка текстурного объекта (texIndex) к текстурному блоку (GL_TEXTURE_2D)
	glBindTexture(GL_TEXTURE_2D, texIndex);

	//Загрузка изображения из оперативной памяти в текстурный объект
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	delete[] pixels;

	//Генерация mipmap’ов.
	glGenerateMipmap(GL_TEXTURE_2D);
	//Установка параметров текстуры.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::apply(TextureFilter) {
	glBindTexture(GL_TEXTURE_2D, texIndex);

}

void Texture::disableAll() {
	glBindTexture(GL_TEXTURE_2D, 0);
}