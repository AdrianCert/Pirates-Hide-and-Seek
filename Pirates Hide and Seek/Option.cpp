#include "GameSelect.h"
using namespace sf;

bool Option(SceneManager* sceneManager) {
	Mouse mouse;
	Font font;

	Vector2u SizeWindow = sceneManager->RenderWindow->getSize();
	float align_left = sceneManager->RenderWindow->getSize().x * 0.25f;
	float align_right = sceneManager->RenderWindow->getSize().x * 0.75f;
	float align_center = sceneManager->RenderWindow->getSize().x * 0.5f;

	if(!font.loadFromFile("Resource/fontTitlu.ttf")) return false;


	Text SFX, SFX_off, SFX_on,
		MUSIC, MUSIC_off, MUSIC_on, 
		RESET_progres,
		RESET_settings,
		back;

	SFX.setFont(font);
	SFX.setString("SFX");
	SFX.setFillColor(Color::Black);
	SFX.setCharacterSize(46);
	SFX.setPosition(align_left, 200);

	SFX_on.setFont(font);
	SFX_on.setString("on");
	SFX_on.setFillColor(Color::Black);
	SFX_on.setCharacterSize(46);
	SFX_on.setPosition(align_right, 200);

	SFX_off.setFont(font);
	SFX_off.setString("off");
	SFX_off.setFillColor(Color::Black);
	SFX_off.setCharacterSize(46);
	SFX_off.setPosition(align_right, 200);

	MUSIC.setFont(font);
	MUSIC.setString("MUSIC");
	MUSIC.setFillColor(Color::Black);
	MUSIC.setCharacterSize(46);
	MUSIC.setPosition(align_left, 400);

	MUSIC_on.setFont(font);
	MUSIC_on.setString("on");
	MUSIC_on.setFillColor(Color::Black);
	MUSIC_on.setCharacterSize(46);
	MUSIC_on.setPosition(align_right, 400);

	MUSIC_off.setFont(font);
	MUSIC_off.setString("off");
	MUSIC_off.setFillColor(Color::Black);
	MUSIC_off.setCharacterSize(46);
	MUSIC_off.setPosition(align_right, 400);

	RESET_progres.setFont(font);
	RESET_progres.setString("reset proges");
	RESET_progres.setFillColor(Color::Black);
	RESET_progres.setCharacterSize(40);
	RESET_progres.setPosition(align_center, 600);

	RESET_settings.setFont(font);
	RESET_settings.setString("reset settigs");
	RESET_settings.setFillColor(Color::Black);
	RESET_settings.setCharacterSize(40);
	RESET_settings.setPosition(align_center, 800);

	back.setFont(font);
	back.setString("back");
	back.setFillColor(Color::Black);
	back.setCharacterSize(46);
	back.setPosition(20, 20);

	int new_sfx;
	int new_music;
	int userAnswer;
	int save_sfx = sceneManager->Settings[GameEnum::OptionField::SFX];
	int save_music = sceneManager->Settings[GameEnum::OptionField::Music];
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Option)
	{
		new_music = -1;
		new_sfx = -1;
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			// Logica butoanelor
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (sceneManager->Settings[GameEnum::OptionField::SFX] == 0) {
					if (isHover(SFX_off, mouse)) {
						new_sfx = 1;
					}
				}
				else {
					if (isHover(SFX_on, mouse)) {
						new_sfx = 0;
					}
				}
				if (sceneManager->Settings[GameEnum::OptionField::Music] == 0) {
					if (isHover(MUSIC_off, mouse)) {
						new_music = 1;
					}
				}
				else {
					if (isHover(MUSIC_on, mouse)) {
						new_music = 0;
					}
				}

				if (isHover(RESET_progres, mouse)) {
					userAnswer = UInterogationWindowForConfirm(sceneManager->RenderWindow, "Are you sure you want to\nreset the progress?", true);
					if (userAnswer == 1)
					{
						cfg::SetParm(sceneManager->Configurator, "player_progress", 1);
					}
				}
				if (isHover(RESET_settings, mouse)) {
					userAnswer = UInterogationWindowForConfirm(sceneManager->RenderWindow, "Are you sure you want to\nreset the settings?", true);
					if (userAnswer == 1)
					{
						sceneManager->Settings[GameEnum::OptionField::Music] = 1;
						sceneManager->Settings[GameEnum::OptionField::SFX] = 1;
					}
				}
				if (isHover(back, mouse)) {
					sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					userAnswer = UInterogationWindowForConfirm(sceneManager->RenderWindow, "Save curent changes?", true);
					if (userAnswer == 1)
					{
						sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					}
					if (userAnswer == 0)
					{
						sceneManager->Settings[GameEnum::OptionField::Music] = save_music;
						sceneManager->Settings[GameEnum::OptionField::SFX] = save_sfx;
						return true;
					}
					if (userAnswer == -1)
					{
						sceneManager->CurentFrame = GameEnum::GameFrame::Option;
					}
				}
			}

			switch (event.type)
			{
			case Event::Closed:
				sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					userAnswer = UInterogationWindowForConfirm(sceneManager->RenderWindow, "Save curent changes?", true);
					if (userAnswer == 1)
					{
						sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					}
					if (userAnswer == 0)
					{
						sceneManager->Settings[GameEnum::OptionField::Music] = save_music;
						sceneManager->Settings[GameEnum::OptionField::SFX] = save_sfx;
						return true;
					}
					if (userAnswer == -1)
					{
						sceneManager->CurentFrame = GameEnum::GameFrame::Option;
					}
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		if (new_sfx != -1) {
			sceneManager->Settings[GameEnum::OptionField::SFX] = new_sfx;
		}
		if (new_music != -1) {
			sceneManager->Settings[GameEnum::OptionField::Music] = new_music;
		}
		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(SFX);
		sceneManager->RenderWindow->draw(MUSIC);
		sceneManager->RenderWindow->draw(RESET_progres);
		sceneManager->RenderWindow->draw(RESET_settings);
		sceneManager->RenderWindow->draw(back);
		if (sceneManager->Settings[GameEnum::OptionField::SFX] == 0) {
			sceneManager->RenderWindow->draw(SFX_off);
		}
		else {
			sceneManager->RenderWindow->draw(SFX_on);
		}
		if (sceneManager->Settings[GameEnum::OptionField::Music] == 0) {
			sceneManager->RenderWindow->draw(MUSIC_off);
		}
		else {
			sceneManager->RenderWindow->draw(MUSIC_on);
		}
		sceneManager->RenderWindow->display();

	}
	cfg::SetParm(sceneManager->Configurator, "music", sceneManager->Settings[GameEnum::OptionField::Music]);
	cfg::SetParm(sceneManager->Configurator, "sfx", sceneManager->Settings[GameEnum::OptionField::SFX]);
	cfg::WriteConfiguration(sceneManager->Configurator, "Resource/ConfigureFile.txt");
	return true;
}