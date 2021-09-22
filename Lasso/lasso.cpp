//Rohan Rajesh Kalbag 
//Roll no : 20d170033
//Indian Institute of Technology Bombay

#include <simplecpp>
//importing of simplecpp features
#include <string>
//for string class
#include <vector>
//for vector class
#include <stdio.h>
//for standard c++ io
#include <stdlib.h>
//for standard c++ library
#include <composite.h>
//for simplecpp graphics objects
#include <sprite.h>
//for simplecpp graphics objects
#include <fstream>
//for input output in file
#include <map>
//for multimap data structure
#include <iterator>
//to access multimap

using namespace simplecpp;

#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

int randint(int a, int b)
{
	int num = (rand() % (b - a + 1)) + a;
	return num;
	//generates a integer between a<=x<=b
	//preconditions: a and b must both be integer values
}

class MovingObject : public Sprite {
	//code given for class declaration Moving Object	
	vector<Sprite*> parts;
	double vx, vy;
	double ax, ay;
	bool paused;
	void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
		vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
	}
	public:
	MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true): Sprite() {
		initMO(argvx, argvy, argax, argay, argpaused);
	}
	MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
		double angle_rad = angle_deg*PI/180.0;
		double argvx = speed*cos(angle_rad);
		double argvy = -speed*sin(angle_rad);
		initMO(argvx, argvy, argax, argay, argpaused);
	}

	void set_vx(double argvx) { vx = argvx; }
	void set_vy(double argvy) { vy = argvy; }
	void set_ax(double argax) { ax = argax; }
	void set_ay(double argay) { ay = argay; }
	double getXPos();
	double getYPos();
	void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);
	void pause() { paused = true; }
	void unpause() { paused = false; }
	bool isPaused() { return paused; }
	void addPart(Sprite* p) {
	parts.push_back(p);
	}
	void nextStep(double t);
	void getAttachedTo(MovingObject *m);
};

#endif

void MovingObject::nextStep(double t) {
	if(paused) { return; }
	for(size_t i=0; i<parts.size(); i++){
		parts[i]->move(vx*t, vy*t);
	}
	vx += ax*t;
	vy += ay*t;
	//a memberfunction of MovingObject Class
} 

double MovingObject::getXPos() {
	return (parts.size() > 0) ? parts[0]->getX() : -1;
	//a memberfunction of MovingObject Class
}

double MovingObject::getYPos() {
	return (parts.size() > 0) ? parts[0]->getY() : -1;
	//a memberfunction of MovingObject Class
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
	for(size_t i=0; i<parts.size(); i++){
		parts[i]->moveTo(argx, argy);
	}
	double angle_rad = angle_deg*PI/180.0;
	double argvx = speed*cos(angle_rad);
	double argvy = -speed*sin(angle_rad);
	vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
	//a memberfunction of MovingObject Class
}

void MovingObject::getAttachedTo(MovingObject *m) {
	double xpos = m->getXPos();
	double ypos = m->getYPos();
	for(size_t i=0; i<parts.size(); i++){
		parts[i]->moveTo(xpos, ypos);
	}
	initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
	//a memberfunction of MovingObject Class
}

#ifndef __COIN_H__
#define __COIN_H__

class Coin : public MovingObject {
	//class for coin and bomb objects	
	double coin_start_x;
	double coin_start_y;
	double release_speed;
	double release_angle_deg;
	double coin_ax;
	double coin_ay;
	Circle coin_circle;
	public:
	vector<int> bomb_properties={0}; 
	//a vector int to store properties of the coin/bomb 
	Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, bool isbomb, int moveforward) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
		release_speed = speed;
		release_angle_deg = angle_deg;
		coin_ax = argax;
		coin_ay = argay;
		if(isbomb)
			bomb_properties[0] = 1;
		initCoin(moveforward);
		//constructor for coin class, is used to create more bombs and coins
		//isbomb = true is for bomb and isbomb=false for coin
		//moveforward is a step value to initialize the x coordinate forward of first coin by moveforward units 
	}
	void initCoin(int moveforward);
	void resetCoin();

};

//various definitions
#endif
#ifndef __LASSO_H__
#define __LASSO_H__
#define WINDOW_X 800
#define WINDOW_Y 600
#define STEP_TIME 0.05
#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)
#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5
#define COIN_GAP 1
#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45
#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 300
#define INIT_RELEASE_SPEED 150
#define COIN_SPEED 200
#define COIN_ANGLE_DEG 90
#define LASSO_G 30
#define COIN_G 50
#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 7

class Lasso : public MovingObject {
	double lasso_start_x;
	double lasso_start_y;
	double release_speed;
	double release_angle_deg;
	double lasso_ax;
	double lasso_ay;

	// Moving parts
	Circle lasso_circle;
	Circle lasso_loop;

	// Non-moving parts
	Line lasso_line;
	Line lasso_band;

	// State info
	bool lasso_looped;
	Coin *the_coin;
	//pointer to the caught coin
	int num_coins;
	//stores the score of player	
	int lives;
	//stores the number of lives remaining
	void initLasso();
	//to initialize the lasso
	public:
	Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
		release_speed = speed;
		release_angle_deg = angle_deg;
		lasso_ax = argax;
		lasso_ay = argay;
		initLasso();
		//constructor for lasso class
	}
	void draw_lasso_band();
	void yank();
	void loopit();
	void addAngle(double angle_deg);
	void addSpeed(double speed);
	void nextStep(double t);
	void check_for_coin(Coin *coin);
	int getNumCoins() { 
		return num_coins; 
		//returns the current score of the player
	}
	int getLives(){
		return lives;
		//returns the remaining number of lives of the player
		
	}

}; 

#endif

void Coin::initCoin(int moveforward) {
	coin_start_x = (PLAY_X_START+WINDOW_X + 2*(moveforward))/2;
	coin_start_y = PLAY_Y_HEIGHT;
	coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
	if(bomb_properties[0]==0){
		coin_circle.setColor(COLOR("green"));
		//set the color of the coins to green
	}
	else
		coin_circle.setColor(COLOR("black"));
		//set the color of the bombs as black
	coin_circle.setFill(true);
	addPart(&coin_circle);
	//a memberfunction of Coin class to initialize the coin/bomb
}

void Coin::resetCoin() {
	double coin_angle_deg = randint(90,170);
	//to give the coin a random startangle 
	coin_ax = randint(-30,30);
	//to give the coin a random acceleration from -30m/s^2 to 30 m/s^2
	coin_ay = COIN_G;
	// all coins and bombs have same acceleration along y direction
	bool paused = true, rtheta = true;
	double coin_speed = randint(180,220);
	// to initialize the speed of coin a random value from 180 to 220
	coin_start_x = (PLAY_X_START+WINDOW_X + 2*(randint(0,300)))/2;
	// to randomize the x coordinate of the coin and bomb to a value that lies between midpoint of screen and 300 pixels ahead of it
	reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
	//reset all stuff of the object of Moving object class
	
	
	//a memberfunction of Coin class to reinitialize the coin/bomb once it returns back to the start point
}

void Lasso::draw_lasso_band() {
	double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
	double arad = release_angle_deg*PI/180.0;
	double xlen = len*cos(arad);
	double ylen = len*sin(arad);
	lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
	lasso_band.setThickness(LASSO_THICKNESS);
	//to draw the band of the lasso i.e the moving rope  
} 

void Lasso::initLasso() {
	lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
	lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
	lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_RADIUS);
	lasso_circle.setColor(COLOR("red"));
	//the lasso circle is the big circle of influence of the lasso that the lasso has reach to
	lasso_circle.setFill(false);
	//the contents of the lasso rope must be seen
	lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
	lasso_loop.setColor(COLOR("red"));
	//the lasso loop of smaller red circle to see the center of the lasso object
	lasso_loop.setFill(true);
	//must be visible inside
	addPart(&lasso_circle);
	addPart(&lasso_loop);
	//add these parts to the loop and fix em together
	lasso_looped = false;
	the_coin = NULL;
	//the coin pointer points to NULL
	num_coins = 0;
	//the initial score is 0
	lives = 3;
	//the initial number of lives is 3.
	lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
	lasso_line.setColor(COLOR("blue"));
	//color of rope
	lasso_band.setColor(COLOR("red"));
	//color of the band
	draw_lasso_band();
	//to initialize the lasso object
} 

void Lasso::yank() {
	bool paused = true, rtheta = true;
	reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
	lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
	lasso_circle.reset(lasso_start_x,lasso_start_y,LASSO_RADIUS);
	lasso_circle.setFill(false);
	lasso_loop.setFill(true);
	lasso_looped = false;
	if(the_coin != NULL) {
		if(((*(the_coin)).bomb_properties[0] == 1)){
			lives = lives - 1;
			//deduct lives if caught coin object is a bomb
		}
		else{
			num_coins++;
			//increment score if caught object is a coin
		}
		the_coin->resetCoin();
		the_coin = NULL;
	}
}

void Lasso::loopit() {
	if(lasso_looped) { 
		return; 
	} 
	// Already looped
	lasso_circle.reset(getXPos(),getYPos(),LASSO_SIZE);
	lasso_loop.reset(getXPos(), getYPos(), LASSO_SIZE);
	lasso_loop.setFill(false);
	lasso_looped = true;

	//loopit member function of lasso class
} 

void Lasso::addAngle(double angle_deg) {
	release_angle_deg += angle_deg;
	if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { 
		release_angle_deg = MIN_RELEASE_ANGLE_DEG; 
	}
	if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { 
		release_angle_deg = MAX_RELEASE_ANGLE_DEG; 
	}
	bool paused = true, rtheta = true;
	reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

	//addangle member function of lasso class
}

void Lasso::addSpeed(double speed) {
	release_speed += speed;
	if(release_speed < MIN_RELEASE_SPEED) { 
		release_speed = MIN_RELEASE_SPEED; 
	}
	if(release_speed > MAX_RELEASE_SPEED) { 
		release_speed = MAX_RELEASE_SPEED; 
	}
	bool paused = true, rtheta = true;
	reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
	//addangle member function of lasso class
}

void Lasso::nextStep(double stepTime) {
	draw_lasso_band();
	MovingObject::nextStep(stepTime);
	if(getYPos() > PLAY_Y_HEIGHT) { 
		yank(); 
	}
	lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} 

void Lasso::check_for_coin(Coin *coinPtr) {
	double lasso_x = getXPos();
	double lasso_y = getYPos();
	double coin_x = coinPtr->getXPos();
	double coin_y = coinPtr->getYPos();
	double xdiff = (lasso_x - coin_x);
	double ydiff = (lasso_y - coin_y);
	double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
	if(distance <= LASSO_RADIUS) {
		the_coin = coinPtr;
		the_coin->getAttachedTo(this);
		//grab the coin and attach its coordinates to the lasso 
	}
} 

main_program {
	string name;
	//to store the name of the user 	
	bool initializer = true;
	//to terminate the infinite user interface loop
	int finalscore = -1;
	//to display the final score
	bool hasname = false;
	//bool to check if the name is given by user
	bool isstored = false;
	//bool to check if the name is stored in the leaderboards file
	fstream file;
	// file object to read and write into file object 
	initCanvas("Lasso",WINDOW_X, WINDOW_Y);
	Text A (400,100,"LASSO - THE GAME MODIFIED AND REDESIGNED BY ROHAN RAJESH KALBAG");
	Text B (400,500," ");		
	Text C(400,300," ");	
	while(initializer){					
		if(finalscore==-1 && !hasname){
			C.setMessage(" Welcome! Enter Your Name in the Command Terminal and press Enter");			
			cin>>name;
			//input the name
			hasname = true;
			//set the bool to true
			C.setMessage(" ");
			//hide the text msg
			B.setMessage("Enter a to continue / Enter b to view instructions / Enter c to view Leaderboards / Enter q to quit");
		}				
		else if(finalscore == -1 && hasname){
			B.setMessage("Enter a to continue / Enter b to view instructions / Enter c to view Leaderboards / Enter q to quit");
		}
		else{
			char score[256];
			sprintf(score,"GAME OVER! Your score was %d ! Awesome !",(finalscore));					
			if(!isstored){
				file.open("leaderboards.dat",ios::app);				
				file<<finalscore<<" "<<name<<endl;
				file.close();
				isstored = true;
			}			
			C.setMessage(score);
			B.setMessage("Enter a to continue / Enter b to view instructions / Enter c to view Leaderboards / Enter q to quit");
		}		
		char a;
		cin>>a;
		//the control character
		B.setMessage("");
		A.setMessage("");
		if(a =='a'){					
			C.setMessage("");			
			isstored = false;			
			Text D(400,100,"DO NOT CLICK THIS CANVAS DRAG/SELECT THE WINDOW USING TITLEBAR !! ");		
			int stepCount = 0;
			float stepTime = STEP_TIME;
			float runTime = -1; 
			// sec; -ve means infinite
			float currTime = 0;
			// Draw lasso at start position
			double release_speed = INIT_RELEASE_SPEED; 
			// m/s
			double release_angle_deg = INIT_RELEASE_ANGLE_DEG; 
			// degrees
			double lasso_ax = 0;
			double lasso_ay = LASSO_G;
			bool paused = true;
			bool rtheta = true;
			Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
			//create lasso object
			Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
			b1.setColor(COLOR("blue"));
			Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
			b2.setColor(COLOR("blue"));
			//set x and y axis on canvas
			string msg("Cmd: _");
			Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
			char coinScoreStr[256];
			sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
			Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);
			char liveCount[256];
			sprintf(liveCount,"Lives: %d",lasso.getLives());
			Text Livescore(PLAY_X_START+200, PLAY_Y_HEIGHT+50, liveCount);
			paused = true; rtheta = true;
			double coin_speed = COIN_SPEED;
			double coin_angle_deg = COIN_ANGLE_DEG;
			double coin_ax = 0;
			double coin_ay = COIN_G;
			Coin coin(coin_speed, 30, coin_ax, coin_ay, paused, rtheta,false,50);
			Coin bomb(coin_speed - 20, 45, coin_ax, coin_ay, paused, rtheta,true,75);
			Coin coin1(coin_speed, 60, coin_ax, coin_ay, paused, rtheta,false,100);
			Coin bomb1(coin_speed - 20, 90, coin_ax, coin_ay, paused, rtheta,true,125);
			Coin coin2(coin_speed, 120, coin_ax, coin_ay, paused, rtheta,false,150);
			Coin bomb2(coin_speed - 20, 135, coin_ax, coin_ay, paused, rtheta,true,175);
			Coin coin3(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta,false,200);
			Coin bomb3(coin_speed - 20, 150, coin_ax, coin_ay, paused, rtheta,true,225);
			//the constructors for all the coin and bomb objects
			// After every COIN_GAP secs, make the coins and bombs jump
			double last_coin_jump_end = 0;
			double last_bomb_jump_end = 0;
			double last_coin1_jump_end = 0;
			double last_bomb1_jump_end = 0;
			double last_coin2_jump_end = 0;
			double last_bomb2_jump_end = 0;
			double last_coin3_jump_end = 0;
			double last_bomb3_jump_end = 0;
			// When t is pressed, throw lasso
			// If lasso within range, make coin stick
			// When y is pressed, yank lasso
			// When l is pressed, loop lasso
			// When q is pressed, quit
			bool temp = true; 
			while(temp) {
				if((runTime > 0) && (currTime > runTime)) { break; }
				XEvent e;
				bool pendingEv = checkEvent(e);
				if(pendingEv) {
					char c = charFromEvent(e);
					msg[msg.length()-1] = c;
					charPressed.setMessage(msg);
					switch(c) {
						case 't':{
							lasso.unpause();
							break;
							//start moving the lasso
						}
						case 'y':{
							lasso.yank();
							break;
							//yank
						}							
						case 'l':{
							lasso.loopit();
							lasso.check_for_coin(&coin);
							lasso.check_for_coin(&coin1);
							lasso.check_for_coin(&coin2);
							lasso.check_for_coin(&coin3);
							lasso.check_for_coin(&bomb);
							lasso.check_for_coin(&bomb1);
							lasso.check_for_coin(&bomb2);
							lasso.check_for_coin(&bomb3);							
							wait(STEP_TIME*5);
							break;
							//loopit
						}
						case '[':{
							if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
							break;
						}
						case ']':{
							if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
							break;
						}
						case '-':{
							if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
							break;
						}
						case '+':{
							if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
							break;
						}
						case 'q':{
							finalscore = lasso.getNumCoins();						
							//set the finalscore variable to the finalscore of the coins						
							temp = false;
							//terminate the loop by setting the bool as false
						}
						default:
							break;
					}
				}
				//for the nextstep function of MovingObject class
				lasso.nextStep(stepTime);
				coin.nextStep(stepTime);
				bomb.nextStep(stepTime);
				coin1.nextStep(stepTime);
				bomb1.nextStep(stepTime);
				coin2.nextStep(stepTime);
				bomb2.nextStep(stepTime);
				coin3.nextStep(stepTime);
				bomb3.nextStep(stepTime);

				if(coin.isPaused()) {
					//check if the coin is paused 
					if((currTime-last_coin_jump_end) >= COIN_GAP) {
						coin.unpause();
					}
				}

				if(coin.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					coin.resetCoin();
					last_coin_jump_end = currTime;
				}

				if(coin.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					coin.resetCoin();
					last_coin_jump_end = currTime;
				}

				if(coin.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					coin.resetCoin();
					last_coin_jump_end = currTime;
				}

				if(coin1.isPaused()) {
					//check if the coin is paused 
					if((currTime-last_coin1_jump_end) >= COIN_GAP) {
						coin1.unpause();
					}
				}

				if(coin1.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					coin1.resetCoin();
					last_coin1_jump_end = currTime;
				}

				if(coin1.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					coin1.resetCoin();
					last_coin1_jump_end = currTime;
				}

				if(coin1.getXPos() < PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					coin1.resetCoin();
					last_coin1_jump_end = currTime;
				}


				if(coin2.isPaused()) {
					//check if the coin is paused 
					if((currTime-last_coin2_jump_end) >= COIN_GAP) {
						coin2.unpause();
					}
				}
				
				if(coin2.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					coin2.resetCoin();
					last_coin2_jump_end = currTime;
				}


				if(coin2.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					coin2.resetCoin();
					last_coin2_jump_end = currTime;
				}

				if(coin2.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					coin2.resetCoin();
					last_coin2_jump_end = currTime;
				}


				if(coin3.isPaused()) {
					//check if the coin is paused 
					if((currTime-last_coin3_jump_end) >= COIN_GAP) {
						coin3.unpause();
					}
				}


				if(coin3.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					coin3.resetCoin();
					last_coin3_jump_end = currTime;
				}


				if(coin3.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					coin3.resetCoin();
					last_coin3_jump_end = currTime;
				}

				if(coin3.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					coin3.resetCoin();
					last_coin3_jump_end = currTime;
				}

				// For Bombs
				if(bomb.isPaused()) {
					//check if the bomb is paused 
					if((currTime-last_bomb_jump_end) >= COIN_GAP) {
						bomb.unpause();
					}
				}

				if(bomb.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					bomb.resetCoin();
					last_bomb_jump_end = currTime;
				}

				if(bomb.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					bomb.resetCoin();
					last_bomb_jump_end = currTime;
				}

				if(bomb.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					bomb.resetCoin();
					last_bomb_jump_end = currTime;
				}


				if(bomb1.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					bomb1.resetCoin();
					last_bomb1_jump_end = currTime;
				}
				
				if(bomb1.isPaused()) {
					//check if the bomb is paused 
					if((currTime-last_bomb1_jump_end) >= COIN_GAP) {
						bomb1.unpause();
					}
				}

				if(bomb1.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					bomb1.resetCoin();
					last_bomb1_jump_end = currTime;
				}

				if(bomb1.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					bomb1.resetCoin();
					last_bomb1_jump_end = currTime;
				}

				if(bomb2.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					bomb2.resetCoin();
					last_bomb2_jump_end = currTime;
				}
				
				if(bomb2.isPaused()) {
					//check if the bomb is paused 
					if((currTime-last_bomb2_jump_end) >= COIN_GAP) {
						bomb2.unpause();
					}
				}

				if(bomb2.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					bomb2.resetCoin();
					last_bomb2_jump_end = currTime;
				}

				if(bomb2.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					bomb2.resetCoin();
					last_bomb2_jump_end = currTime;
				}


				if(bomb3.getYPos() > PLAY_Y_HEIGHT) {
					//if the coin/bomb goes out of playzone reset it
					bomb3.resetCoin();
					last_bomb3_jump_end = currTime;
				}

				if(bomb3.isPaused()) {
					//check if the bomb is paused 
					if((currTime-last_bomb3_jump_end) >= COIN_GAP) {
						bomb3.unpause();
					}
				}

				if(bomb3.getXPos() > WINDOW_X ) {
					//if the coin/bomb goes out of playzone reset it
					bomb3.resetCoin();
					last_bomb3_jump_end = currTime;
				}

				if(bomb3.getXPos()<PLAY_X_START){
					//if the coin/bomb goes out of playzone reset it
					bomb3.resetCoin();
					last_bomb3_jump_end = currTime;
				}
				sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
				coinScore.setMessage(coinScoreStr);
				//change the coinscore in each pass of the while loop
				if(lasso.getLives() == 0){
					//after all three lives get exhausted
					finalscore = lasso.getNumCoins();
					//set the finalscore variable to the finalscore of the coins						
					temp = false;
					//terminate the loop by setting the bool as false
					
				}					
				sprintf(liveCount,"Lives: %d",lasso.getLives());
				Livescore.setMessage(liveCount);
				//show the no of lives on the canvas
				stepCount++;
				currTime += stepTime;
				wait(stepTime);
			} 			
											
		}
		else if(a =='b'){
			//open the readme file in the same directory and pop it up for the user
			system("gedit readme");

		}			
		else if(a =='c'){			
			//to checkout the leaderboards
			multimap <int,string, greater<int>> s;
			//multimap datastructure in descending order sorting format
			{
				file.open("leaderboards.dat",ios::in);
				//open leaderboards.dat file
				int i;
				while(file>>i){
					string j;
					file >> j;
					s.insert(make_pair(i,j));
				}
				file.close();		
			}
			{	
				//to display the sorted leaderboards in leaderboard.dat
				file.open("leaderboards.dat",ios::out |ios::trunc);
				map<int,string> :: iterator it;
				for(it = s.begin() ; it != s.end() ; it++) {			
					file << (*it).first << " " << (*it).second <<endl;
				} 
				file.close();	
			}
			//open the file leaderboards.dat and pop it up for the user
			system("gedit leaderboards.dat");

		}	
		else if(a =='q'){
			//terminate the total program
			initializer = false;
		}			
	}
} 

