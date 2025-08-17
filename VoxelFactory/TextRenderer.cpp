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

void TextRenderer::render() {
	glPushMatrix();

	int wordLetters = 1;

	for (int i = 0; i < _characterSprites.size(); i++) {
		glTranslatef(_characterOffset, 0, 0.0f);

		if (_text[i] == '_') {
			glTranslatef(wordLetters * -_characterOffset, -_characterOffset, 0.0f);
			wordLetters = 1;
		}
		else {
			_characterSprites[i]->render();
			wordLetters++;
		}
	}

	glPopMatrix();
}

Component* TextRenderer::copy() {
	return new TextRenderer(_text);
}