#pragma once
#include "Entity.h"
#include "Game_State.h"

class Battle_State : public Game_State
{
public:
	Battle_State(Game_State**, Game_State*);
	Game_State* enter();
	void exit();
	void processInput(sf::RenderWindow&);
	void update(sf::RenderWindow&, std::vector<Entity*>&);
	void render(sf::RenderWindow&, std::vector<Entity*>&);

	static bool slow_time;

	//Struct UI
	struct battle_UI
	{
		//battle_UI Constructor and Methods
		battle_UI();
		void update(Enemy**, Ally**, int);
		void render(sf::RenderWindow&, int);
		void createEnemyHealthBar();
		void createEnemyATPBar();
		void createPartyHealthBar();
		void createPartyATPBar();
		void createPartySPBar();
		void create(Ally**, int, int);
		void openCommand();
		void closeCommand();
		void scrollDown();
		void scrollUp();
		//Struct Health Bar
		struct Bar
		{
			sf::Vertex vertices[4];
			void createBar(sf::Vector2f, sf::Vector2f);
			void render(sf::RenderWindow&);
			void setWidth(float);
			void setThickness(int);
			void setColor(sf::Color, sf::Color);
			void setMaxWidth(float);
			bool isFilled();
			float getWidth();
			float thickness = 7;
			float width = 1;
			float maxWidth = 600;
			sf::Color color1;
			sf::Color color2;
		};
		Bar enemyHP[MAX_ENEMIES];
		Bar enemyATP[MAX_ENEMIES];
		Bar partyHP[MAX_PARTY];
		Bar pHP_bg[MAX_PARTY];
		Bar pSP_bg[MAX_PARTY];
		Bar partyATP[MAX_PARTY][2];
		Bar partySP[MAX_PARTY];
		//Boxes
		sf::Vertex command_Box[4];
		sf::Vertex party_Box[4];
		sf::RectangleShape select_icon_box;
		//Texts
		sf::Text command_text;
		sf::Text party_names_text[MAX_PARTY];
		sf::Text party_hp_text[MAX_PARTY];
		sf::Text party_sp_text[MAX_PARTY];
		sf::Text ability_texts[3];
		sf::Font font;
		std::string atwo_hp;
		std::string twob_hp;
		std::string nines_hp;
		std::string atwo_sp;
		std::string twob_sp;
		std::string nines_sp;
		//Primitives
		bool command_open = false;
		int selected_ability = 0;
		int enemy_size, party_size;
	};
private:
	//<!> Delete Later - Apply the Entity Array or not...
	ATwo aTwo;
	TwoB twoB;
	NineS nineS;
	//<!> May change to Enemy* type for subclass of enemies
	Enemy* enemy_array[MAX_ENEMIES];
	Ally* party_array[MAX_PARTY];
	//For Battle System
	sf::RectangleShape select_icon_;
	sf::RectangleShape current_party_icon;
	sf::Vector2f select_offset_;
	battle_UI battle_ui;
	bool show_select_ = false;
	bool switched = false;
	bool win = false;
	bool lose = false;
	int party_size_ = 0, enemy_size_ = 0;
	int switched_from = 0;
	int active_party_member = 0;
	int timer = 0;
	const int basic_attack_ = 0;
	const int first_member = 0;
	const int max_timer = 600;
	//Methods
	void initializeParty();
	void initializeEnemies();
	void nextPartyMember();
	void switchPartyMember(int);
	void switchBack();
	void controlTimer();
	void checkVictory();
	void checkDefeat();
	//Audio
	sf::Music battle_music_;
	//Pointer to current_State pointer in Game Class
	Game_State** ptr_to_ptr_to_current_State_;
	//Pointer to the test_State object in the Game Class
	Game_State* next_State_;
};