#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title.loadFromRenderedText("Highscore", color, renderer);
	newGame.setText("New game", color, renderer);
	quit.setText("Quit game", color, renderer);
	conn = NULL;
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

void HighScoreScreen::connectDB()
{
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, NULL, 0);

	if (!conn)
	{
		std::cerr << "Failed to connect to database: Error: " << mysql_error(conn);
	}
}

void HighScoreScreen::closeDB()
{
	mysql_close(conn);
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

void HighScoreScreen::show_stmt_error(MYSQL_STMT* stmt)
{
	printf("Error(%d) [%s] \"%s\"", mysql_stmt_errno(stmt),
		mysql_stmt_sqlstate(stmt),
		mysql_stmt_error(stmt));
	exit(-1);
}

void HighScoreScreen::submitScore(int* score, std::string name)
{
	MYSQL_STMT* stmt;
	MYSQL_BIND bind[3];
	/* Data for insert */
	std::string query = "INSERT INTO Highscore VALUES (?,?,?)";
	char id_ind[] = { STMT_INDICATOR_NULL };
	unsigned long nameLen = static_cast<unsigned long>(name.size());
	unsigned int array_size = 1;

	stmt = mysql_stmt_init(conn);
	if (mysql_stmt_prepare(stmt, query.c_str(), static_cast<unsigned long>(query.size())))
	{
		show_stmt_error(stmt);
	}
	memset(bind, 0, sizeof(MYSQL_BIND) * 3);

	/* We autogenerate id's, so all indicators are STMT_INDICATOR_NULL */
	bind[0].u.indicator = id_ind;
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &name[0];
	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer_length = nameLen;
	bind[1].length = &nameLen;

	bind[2].buffer_type = MYSQL_TYPE_LONG;
	bind[2].buffer = score;

	/* bind parameter */
	mysql_stmt_bind_param(stmt, bind);

	/* execute */
	if (mysql_stmt_execute(stmt))
		show_stmt_error(stmt);

	mysql_stmt_close(stmt);
	
}