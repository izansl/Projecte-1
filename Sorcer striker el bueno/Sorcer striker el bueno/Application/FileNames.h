#pragma once

#ifndef FILENAMES_H
#define FILENAMES_H

#include <string>


// --------|  FILE+TYPE_CATEGORY_NAME = PATH  |--------


#pragma region IMAGES -> FI
//IntroImages
//cambiar a png //cambiar ruta a ImagenesIntro2
const std::string FI_Introimage_1 = "../Assets/Images/ImagenesIntro2/intro1.png";
const std::string FI_Introimage_2 = "../Assets/Images/ImagenesIntro2/intro2.png";
const std::string FI_Introimage_3 = "../Assets/Images/ImagenesIntro2/intro3.png";
const std::string FI_Introimage_4 = "../Assets/Images/ImagenesIntro2/intro4.png";
const std::string FI_Introimage_5 = "../Assets/Images/ImagenesIntro2/intro5.png";
const std::string FI_Introimage_6 = "../Assets/Images/ImagenesIntro2/intro6.png";
const std::string FI_Introimage_7 = "../Assets/Images/ImagenesIntro2/intro7.png";
const std::string FI_Introimage_8 = "../Assets/Images/ImagenesIntro2/intro8.png";
const std::string FI_Introimage_9 = "../Assets/Images/ImagenesIntro2/intro9.png";
const std::string FI_Introimage_10 = "../Assets/Images/ImagenesIntro2/intro10.png";
const std::string FI_Introimage_11 = "../Assets/Images/ImagenesIntro2/intro11.png";
const std::string FI_Introimage_12 = "../Assets/Images/ImagenesIntro2/intro12.png";

// Backgrounds
const std::string FI_background_beach = "../Assets/Images/Beach.png";
const std::string FI_background_sea = "../Assets/Images/Sea.png";
const std::string FI_background_forest1 = "../Assets/Images/Forest_1.png";
const std::string FI_background_forest2 = "../Assets/Images/Forest_2.png";
const std::string FI_background_castle = "../Assets/Images/Castle.png";
const int Height_background_beach = 3000;
const int Height_background_sea = 4500;
const int Height_background_forest1 = 3000;
const int Height_background_forest2 = 3000;
const int Height_background_castle = 4500;

//HUD
const std::string FI_HUD_font1 = "../Assets/Images/Fonts/rtype_font.png";
const std::string FI_HUD_font2 = "../Assets/Images/Fonts/rtype_font2.png";
const std::string FI_HUD_stage1 = "../Assets/Images/Fonts/stage1.png";

// Sprites player
const std::string FI_spritePlayer_player1 = "../Assets/Images/Character.png";
const std::string FI_spritePlayer_player2 = "../Assets/Images/Character.png";
//const std::string FI_spriteEnemy_1 = "../Assets/Images/SPRITES-1080/pre-castillo/naves.png";
// Sprites enemys
//const std::string FI_spriteEnemy_1 = "../Assets/Images/1st_enemy.png";
/*-Movement
1 - ({ 43, 12, 32, 32 })
2 - ({ 73, 12, 32, 32 })
- Explosion
1 - ({ 7, 50, 32, 32 })
2 - ({ 42, 50, 32, 32 })
3 - ({ 77, 51, 32, 32 })
4 - ({ 111, 52, 32, 32 })
*/
const std::string FI_spriteEnemy_1 = "../Assets/Images/SPRITES-1080/pre-castillo/enemies.png";
//red ball
//({29, 357, 82, 104})
//({140, 357, 82, 104})
//mago
//({0, 798, 131, 132})frente
//({0, 955, 131, 132})frente
//({159, 802, 131, 132})giro derecha inicio
//({320, 801, 131, 132})giro derecha medio
//({493, 802, 131, 132})giro derecha final
//({197, 956, 131, 132}) giro izquierda inicio
//({324, 956, 131, 132})giro izquierda medio
//({491, 957, 131, 132})giro izquierda final
//mago herido
//({0, 487, 131, 132})frente
//({0, 635, 131, 132}) frente
//({170, 497, 131, 132})giro derecha inicio
//({325, 647, 131, 132})giro derecha medio
//({493, 648, 131, 132})giro derecha final
//({167, 650, 131, 132})giro izquierda inicio
//({329, 493, 131, 132})giro izquierda medio
//({491, 495, 131, 132})giro izquierda final
// disparo mago
//({640, 521, 99, 79})
//({861, 521, 99, 79 })
//({1007, 528, 99, 79})
//({933, 528, 99, 79 })
//({731, 527, 99, 79})
//explosion
//({1, 136, 139, 137})
//({155, 140, 139, 137})
//({335, 142, 139, 137})
//({586, 139, 139, 137})
//({644, 142, 139, 137})
//({798, 142, 139, 137})

const std::string FI_spriteEnemy_2 = "../Assets/Images/2nd_enemy.png";
/*-Movement
		1-({4, 22, 36, 36})
		2-({41, 22, 36, 36 })
	-Explosion
		1-({3, 71, 36, 36})
		2-({39, 72, 36, 36 })
		3-({75, 72, 36, 36 })
		4-({111, 71, 36, 36})
	Atack
		1-({82, 30 , 20, 20})
		2-({102, 31, 20, 20})
		3-({121, 30, 20, 20})	*/
//const std::string FI_spriteEnemy_3 = "../Assets/Images/3rd_enemy.png";
/*	-Movement
		1-({15, 24, 90, 90})
		2-({115, 24, 90, 90})
	-Explosion
		1-({17, 121, 90, 90})
		2-({111, 124, 90, 90})
		3-({204, 123, 90, 90})
	Atack
		1-({229, 77, 15, 15})
		2-({245, 77, 15, 15})*/
const std::string FI_spriteEnemy_3 = "../Assets/Images/SPRITES-1080/pre-castillo/dragon.png";

//Sprites chest
const std::string FI_spritechest_blue = "../Assets/Images/Chests.png";
/*	-Bluechest
		-Hada con cofre
			1-({2, 7, 43, 39 })
			2-({47, 7, 43, 39 })
			3-({94, 7, 43, 39 })
		-Librobuff
			1-({58, 20, 15, 20 })
			2-({72, 54, 15, 20})
*/


// Sprites Bosses
const std::string FI_spriteBoss_boss1 = "../Assets/Images/Beach.png";
const std::string FI_spriteEnemy_boss = "../Assets/Images/SPRITES-1080/final-boss/finalboss.png";
//warning
// ({30, 13, 778, 113}) rojo
// ({31, 150, 778, 113}) azul
// flecha
// ({894, 195, 108, 130})
// //cabeza
// ({826, 0, 115, 177}) herido
// ({970, 3, 115, 177}) normal
// ventilador
// ({650, 284, 109, 102})
// ({765, 386, 778, 113})
// cuerpo
// ({77, 451, 868, 380})
// ({77, 451, 868, 380})
// cuerpo destruido
// ({1286, 473, 868, 380})
// ({1278, 917, 868, 380})
// 
// 
//explosion enemiga
const std::string FI_spriteExplosion_enemies = "../Assets/Images/2nd_enemy.png";
#pragma endregion



#pragma region AUDIOS -> FA
// General
const std::string FA_Fx_token = "../Assets/Audios/FX/token-insertado.wav";

// Init
const std::string FA_Music_introTitle = "../Assets/Audios/Hud-music/musica-menu.ogg";

// Level 1
const std::string FA_Music_stage1 = "../Assets/Audios/Stage-1/stage1.ogg";

// Explosion enemiga
const std::string FA_Fx_explosion = "../Assets/Audios/FX/explosion-muerte-enemiga.wav";

//Explosion jugador
const std::string FA_Fx_explosionJ = "../Assets/Audios/FX/explosion(jugador-muerto).wav";
// Level 2

// Level 3

// Level 4

// Level 5

// Level 6

// Level 7

#pragma endregion



#endif