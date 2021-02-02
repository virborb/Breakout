#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title.loadFromRenderedText("Highscore", color, renderer);
	newHighscore.loadFromRenderedText("New Highscore, Enter name to submit score.", color, renderer);
	inputRect = { Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 25, Window::SCREEN_HEIGHT / 2, 250, 20 };
	newGame.setText("New game", color, renderer);
	quit.setText("Quit game", color, renderer);
	submit.setText("Submit score", color, renderer);
	conn = NULL;
	renderInput = true;
}

Action HighScoreScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return Action::NewGame;
	}
	else if (quit.handleEvent(e))
	{
		return Action::Quit;
	}
	else if (submit.handleEvent(e))
	{
		return Action::Submit;
	}
	if (e->type == SDL_KEYDOWN)
	{
		//Handle backspace
		if (e->key.keysym.sym == SDLK_BACKSPACE && input.length() > 0)
		{
			//lop off character
			input.pop_back();
			renderInput = true;
		}
		//Handle copy
		else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(input.c_str());
		}
		//Handle paste
		else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			input = SDL_GetClipboardText();
			renderInput = true;
		}
	}
	else if (e->type == SDL_TEXTINPUT)
	{
		//Not copy or pasting
		if (!(SDL_GetModState() & KMOD_CTRL && (e->text.text[0] == 'c' || e->text.text[0] == 'C' || e->text.text[0] == 'v' || e->text.text[0] == 'V')))
		{
			//Append character
			if (input.size() < 30)
			{
				input += e->text.text;
				renderInput = true;
			}
		}
	}
	return Action::NoAction;
}

void HighScoreScreen::render(SDL_Renderer* renderer)
{
	title.render(Window::SCREEN_WIDTH / 2 - title.getWidth() / 2, Window::SCREEN_HEIGHT/2 - 90, renderer);
	int positionY = -75;
	for (auto& score : scores)
	{
		score->name.render(Window::SCREEN_WIDTH / 2 - 150, Window::SCREEN_HEIGHT / 2 + positionY, renderer);
		score->score.render(Window::SCREEN_WIDTH / 2 + 100, Window::SCREEN_HEIGHT / 2 + positionY, renderer);
		positionY += 15;
	}
	positionY += 20;
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 10, Window::SCREEN_HEIGHT / 2 + positionY);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + 10, Window::SCREEN_HEIGHT / 2 + positionY);
	newGame.render(renderer);
	quit.render(renderer);
}

void HighScoreScreen::renderNewHighscore(SDL_Renderer* renderer)
{
	if (renderInput)
	{
		SDL_Color color = { 0, 0xFF, 0 };
		//Text is not empty
		if (input != "")
		{
			//Render new text
			inputText.loadFromRenderedText(input.c_str(), color, renderer);
		}
		//Text is empty
		else
		{
			//Render space texture
			inputText.loadFromRenderedText(" ", color, renderer);
		}
	}
	newHighscore.render(Window::SCREEN_WIDTH / 2 - newHighscore.getWidth() / 2, Window::SCREEN_HEIGHT / 2 - 20, renderer);
	inputText.render(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 20, Window::SCREEN_HEIGHT / 2, renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
	SDL_RenderDrawRect(renderer, &inputRect);
	submit.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() / 2 - submit.getWidth() - 5, Window::SCREEN_HEIGHT / 2 + 25);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() / 2, Window::SCREEN_HEIGHT / 2 + 25);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + newGame.getWidth() / 2 + 5, Window::SCREEN_HEIGHT / 2 + 25);
	submit.render(renderer);
	newGame.render(renderer);
	quit.render(renderer);
	renderInput = false;
}

void HighScoreScreen::connectDB()
{
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, NULL, 0);

	if (!conn)
	{
		std::cerr << "Failed to connect to database: Error: " << mysql_error(conn);
	}
}

void HighScoreScreen::collectHighscores(SDL_Renderer* renderer)
{
	int qstate = -1;
	MYSQL_ROW row;
	MYSQL_RES* res;
	SDL_Color color = { 0, 0xFF, 0 };
	std::string query = "SELECT * FROM `Highscore` ORDER BY `Score` DESC LIMIT 10";
	const char* q = query.c_str();
	if (conn)
	{
		qstate = mysql_query(conn, q);
	}
	scores.clear();
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			Highscore* highscore = new Highscore();
			highscore->name.loadFromRenderedText(row[1], color, renderer);
			highscore->score.loadFromRenderedText(row[2], color, renderer);
			scores.push_back(highscore);
		}
	}
	else
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		Highscore* highscore = new Highscore();
		highscore->name.loadFromRenderedText("Failed to get highscores", color, renderer);
		scores.push_back(highscore);
	}
}

bool HighScoreScreen::checkNewHighscore(int score, SDL_Renderer* renderer)
{
	int qstate = -1;
	MYSQL_ROW row;
	MYSQL_RES* res;
	SDL_Color color = { 0, 0xFF, 0 };
	std::string query = "SELECT COUNT(*) FROM `Highscore` WHERE `Score` > " + std::to_string(score);
	const char* q = query.c_str();
	if (conn)
	{
		qstate = mysql_query(conn, q);
		
	}
	scores.clear();
	if (!qstate)
	{
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		return (std::atoi(row[0]) < 10);
	}
	std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	Highscore* highscore = new Highscore();
	highscore->name.loadFromRenderedText("Failed to check if new highscore", color, renderer);
	scores.push_back(highscore);
	return false;
}