#include "TextRenderer.h"

TextRenderer::TextRenderer(std::string text) {
	setText(text);
}

void TextRenderer::setText(std::string newText) {
	_characterSprites.clear();
	_text = newText;

	for (int i = 0; i < newText.length(); i++) {
		_characterSprites.push_back(new Sprite(*_fontSheet));
		_characterSprites[i]->setCurrentFrame(newText[i] - _firstCharacterASCIIOffset);
	}
}

void TextRenderer::setTextColor(glm::vec3 color) {
	_textColor = color;
}

void TextRenderer::render() {
	glPushMatrix();

	glColor3f(_textColor.r, _textColor.g, _textColor.b);

	int lineLetters = 1;

	for (int i = 0; i < _characterSprites.size(); i++) {
		glTranslatef(_characterOffset, 0, 0.0f);

		if (_text[i] == '\n') {
			glTranslatef(lineLetters * -_characterOffset, -_characterOffset, 0.0f);
			lineLetters = 1;
		}
		else {
			_characterSprites[i]->render();
			lineLetters++;
		}
	}

	glColor3f(1, 1, 1);

	glPopMatrix();
}

Component* TextRenderer::copy() {
	return new TextRenderer(_text);
}