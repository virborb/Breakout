#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title.loadFromRenderedText("Highscore", color, renderer);
	newGame.setText("New game", color, renderer);
	quit.setText("Quit game", color, renderer);
	conn = NULL;
}

int HighScoreScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return NEW_GAME;
	}
	else if (quit.handleEvent(e))
	{
		return QUIT;
	}
	return NO_ACTION;
}

void HighScoreScreen::render(SDL_Renderer* renderer)
{
	title.render(Window::SCREEN_WIDTH / 2 - title.getWidth() / 2, Window::SCREEN_HEIGHT/2 - 90, renderer);
	int positionY = -75;
	for (auto& score : scores)
	{
		score->name.render(Window::SCREEN_WIDTH / 2 - 100, Window::SCREEN_HEIGHT / 2 + positionY, renderer);
		score->score.render(Window::SCREEN_WIDTH / 2 + 50, Window::SCREEN_HEIGHT / 2 + positionY, renderer);
		positionY += 15;
	}
	positionY += 20;
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 10, Window::SCREEN_HEIGHT / 2 + positionY);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + 10, Window::SCREEN_HEIGHT / 2 + positionY);
	newGame.render(renderer);
	quit.render(renderer);

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
			std::stringstream stream;
			stream << row[1] << ' ' << row[2];
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