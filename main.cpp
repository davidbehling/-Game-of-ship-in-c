#include <allegro.h>
#include <iostream>
#include <stdlib.h>

/* metodos sem retorno */
void init();              //cabeçalho do Jogo
void deinit();

void movimento_cenario(); //chama cenario do jogo;
void m_turbina();         //animação da turbina da nave;
void control();           //função de movimentação da nave;
void luzes_ovni();        //animação das luzes do ovni;
void luzes_chefe();       //animação das luzes do chefe do game;
void tiro_animacao();     //animação do tiro;
void tiro2_animacao();    //animação do tiro2;
void tiro3_animacao();    //animação do tiro3;
void tiro_ovni();         //função de tiro do ovni;
void tiro_chefe();        //função de tiro do chefe do game;
void movimento_ovni();    //movimento do ovni na tela;
void movimento_chefao();  //movimento do chefão na tela;
void vida_jogador();      //inicia a vida do jogador;
void animacao_explosao();
void gatilho00();         //descida do chefão na tela
void gatilho01();         //movimentação esquerda e direita do chefão
void gatilho02();         //mudança de velocidade do chefão


/* metodos com retorno */
int colisao_tiro(int ax, int ay, int al, int aa, int bx, int by, int bl, int ba); //cria a colisões;


/* structs globais*/
struct obj{
    int wx, wy; //determina o posicionamento do quadro que contém a sprite;
    int x, y;   //determina as coordenadas onde será posicionada a sprite na tela;
    int l, a;   //a largura e altura da sprite;
};

struct obj jogador = {0,167,325,430,162,167}; //mapeando a sprite da nave;
struct obj inimigo = {0,394,100,-100,248,92};  //mapeando a sprite do ovni;
struct obj chefao = {0,1274,250,-200,249,194}; //mapeando a sprite do chefe do game;
struct obj tiro = {0,561,900,900,27,82};     //mapeando a sprite de tiro;
struct obj tiro2 = {0,893,900,900,67,66};     //mapeando a sprite de tiro2;
struct obj tiro3 = {0,1528,900,900,66,82};    //mapeando a sprite de tiro3;
struct obj explosao = {0,729,900,900,102,101};     //mapeando a sprite de tiro;
struct obj vida[3]; //= {0,1034,10,570,36,26}; mapea a sprite de vida do jogador;


/* variáveis globais*/
int finalizarGame = 0;   //finaliza o game quando o valor for 1;

int cy1=0, cy2=0, cy3=0; //variáveis para movimentos dos cenário;
int cv1=12, cv2=4, cv3=8;//velocidade do movimento dos cenarios;


int turbina = 0;         //determina a mudança de quadros de sprite da nave;
int velocidade = 10;     //velocidade de movimento da nave;


int luz_ovni = 0;        //determina a troca de sprites do ovni;
int luz_chefe = 0;       //determina a troca de sprites do chefe do game;


int atirar = 0;          //determina se o tiro foi disparado ou não;
int tiroanimacao = 0;    //determina a mudança de sprites do tiro;
int tiro2animacao = 0;   //determina a mudança de sprites do tiro2;
int tiro3animacao = 0;   //determina a mudança de sprites do tiro3;


int ovniatirar = 0;      //determina se o tiro do ovni esta carregado;
int ovnidirecao = 0;     //determina direção esquerda ou direita;


int chefaoatirar = 0;     //determina se o tiro do chefe esta carregado;
int chefaodirecao = 0;    //determina direção esquerda ou direita;
int chefaogatilho = 0;    //determina as reações do chefao;
int chefaovida = 20;      //determina os pontos de vida do chefão
int chefaospeedtiro = 10; //determina a velocidade de tiro do chefão;
int chefaospeedmove = 5;  //determina a velocidade de movimento do chefão;
int chefaotiro = 0;       //determina a quantidade de dispaos;


int pontos = 0;          //determina a pontuação de acertos de ovnis destruidos;         /*ALERTE MUDAR PARA VALOR 0 DEPOIS DO ESTE*/
int vidas = 3;           //determina a quantidade de vida do jogador;


int explosaoanimacao = 0;//determina a mudança de sprites da explosão;
int t = 0;
int tempo = 1000000000;


/* implementando controle de tempo */
int timerGame = 0;             //variável para contagem de tempo;
void tempoGame(){timerGame++;} //irá incrementar a variável timeGamer;
float delayGame;               //variável para controle de tempo;
int marcador;                  //variável para controlar tempo de game over ou vitoria;
int marcador2;                 //variável para controlar o tempo de fechamento do jogo;

/* inicio do programa */
int main() {
	
	init();         //chama o cabeçalho do jogo;
	install_int_ex(tempoGame, MSEC_TO_TIMER(25)); //estipulando a cada quantos milessegundos ocorrera a mudança de quadros
   
   
	vida_jogador(); //chama inicialização da vida do jogador;
	

	/* importando imagens do cenário */
	BITMAP *buffer = create_bitmap(800, 600);
	BITMAP *cena1 = load_bitmap("imagens/z_spaco01.bmp", NULL); //importando cenário;
	BITMAP *cena2 = load_bitmap("imagens/z_spaco02.bmp", NULL); //importando cenário;
	BITMAP *cena3 = load_bitmap("imagens/z_spaco03.bmp", NULL); //importando cenário;
	/* importando imagens da navi do jogador */	
	BITMAP *nave = load_bitmap("imagens/projeto.bmp",NULL);
	/* importando imagem de Game Over */
	BITMAP *gameover = load_bitmap("imagens/gameover.bmp", NULL);
	/* importando imagem de Finalização */
	BITMAP *finalizacao = load_bitmap("imagens/final.bmp", NULL);
	
	
	/* musicas do game*/
	MIDI *titleMidi = load_midi("musicas/musicSom.mid");    //importando musicas;    
	play_midi(titleMidi, true); // iniciando musica;
    
   
	/* inicio do loop do game */
	while (!key[KEY_ESC]) {
      
		delayGame = timerGame; //delay receberá o valor de timer;
      
		movimento_cenario(); //chama movimento do cenario;
		m_turbina();         //chama efeito de animação da turbina da nave do jogador
		control();           //chama controle da nave do jogador;
      
      
		//enquanto 10 ovnis não porem destruidos,
		//eles continuação a aparecer.
		if(pontos<10){
			luzes_ovni();      //chama efeito de animação do ovni;
			tiro_ovni();       //chama ação de tiro do ovni;
			movimento_ovni();  //chama ação de movimento do ovni;
		}
      
		//depois que os ovnies forem destruidos,
		//o chefe aparecerá.
		if(pontos==10){
			luzes_chefe();       //chama efeito de animação do chefe;   
			tiro_chefe();        //chama ação de tiro do chefe;
			movimento_chefao();  //chama  ação de movimento do ovni;
		}
      
      
		/* inicialização de imagens */
       
		/* criando inicialização da primeira camanda da imagem do cenário */
		draw_sprite(buffer, cena1, 0, cy1);		
		draw_sprite(buffer, cena1, 0, cy1 - 600 );
		/* criando inicialização das imagens do tiro */
		masked_blit(nave, buffer, tiro.wx = tiroanimacao*27, tiro.wy, tiro.x, tiro.y, tiro.l, tiro.a);
		masked_blit(nave, buffer, tiro2.wx = tiro2animacao*67, tiro2.wy, tiro2.x, tiro2.y, tiro2.l, tiro2.a);
		masked_blit(nave, buffer, tiro3.wx = tiro3animacao*66, tiro3.wy, tiro3.x, tiro3.y, tiro3.l, tiro3.a);
		/* criando inicialização das imagens da nave */		
		masked_blit(nave, buffer, jogador.wx = turbina*162, jogador.wy, jogador.x, jogador.y, jogador.l, jogador.a);		
		/* criando inicialização das imagens do onvi */
		masked_blit(nave, buffer, inimigo.wx = luz_ovni*248, inimigo.wy, inimigo.x, inimigo.y, inimigo.l, inimigo.a);
		/* criando inicialização das imagens do chefe do game */
		if(pontos==10){
			masked_blit(nave, buffer, chefao.wx = luz_chefe*249, chefao.wy, chefao.x, chefao.y, chefao.l, chefao.a);	
		}
		/* criando inicialização da segunda e terceira camada das imagens do cenário */
		draw_sprite(buffer, cena2, 0, cy2);
		draw_sprite(buffer, cena2, 0, cy2 - 600 );
		draw_sprite(buffer, cena3, 0, cy3);		
		draw_sprite(buffer, cena3, 0, cy3 - 600 );
		
		/* irá mostar o time na tela */
		textprintf_ex(buffer, font, 750, 570, makecol(0,0,0),-1,"%d",timerGame); //irá mostrar o timer na tela
      
		/* criando inicialização das imagens da vida do jogador */
		if(vidas>=0){
        
			//jogador com 3 vidas;           
			if(vidas==3){             
				for (int i=0; i<3; i++){		
					masked_blit(nave, buffer, vida[i].wx, vida[i].wy, vida[i].x, vida[i].y, vida[i].l, vida[i].a);
				}
			}	
			//jogador com 2 vidas;  
			if(vidas==2){             
				for (int i=0; i<2; i++){		
					masked_blit(nave, buffer, vida[i].wx, vida[i].wy, vida[i].x, vida[i].y, vida[i].l, vida[i].a);
				}
			}
			//jogador com 1 vida;  
			if(vidas==1){             
				for (int i=0; i<1; i++){		
					masked_blit(nave, buffer, vida[i].wx, vida[i].wy, vida[i].x, vida[i].y, vida[i].l, vida[i].a);
				}
			}
			//jogador com 0 vida;  
			if(vidas==0){             
				jogador.x = 1000;
				jogador.y = 1000;
			}
		}
      
		/* marcando o tempo em que o jogador foi derrotado */
		if(vidas==0){
			vidas = -1;
			marcador = timerGame;      
		}
      
		/* criando inicialização da prite GameOver2 */
		if(vidas==-1){                    
			//depois da derrota do jogador, quando o tempo atual menos o tempo em que o
			//jogador foi derrotado for maior que 'x' milessegundos, será mostrado a tela de GAMEOVER;   
			
			if(timerGame-marcador >= 100){          
					draw_sprite(buffer, gameover, 0, 0);
					if(finalizarGame == 0) marcador2 = timerGame;
					finalizarGame = 1;               
               
			}     
		}
      
		/* criando inicialização da Vitoria */      
		if(chefaovida==-1){         
			//depois de derrotar o chefão, quando o tempo atual menos o tempo em que o
			//chefão foi derrota for maior que 'x' milessegundos, será mostrado a tela de vitória; 
			
			if(timerGame-marcador >= 100){               
                 draw_sprite(buffer, finalizacao, 0, 0);
                 if(finalizarGame == 0) marcador2 = timerGame;
                 finalizarGame = 1;
                 
			}
		}
		
		/* finaliza o programa depois de exibir GameOver ou a Vitoria*/
		if(finalizarGame==1){
                           
         if(timerGame-marcador2 >= 100){               
              //exit(EXIT_SUCCESS);
              break;   
			}
      }
      
		/* colisões */
      
		/*COLISÃO -> JOGADOR VS NAVE INIMIGA*/ 
      
		/*colisão do tiro do jogador na nave inimiga*/
		if(colisao_tiro(tiro.x, tiro.y, tiro.l, tiro.a, inimigo.x, inimigo.y, inimigo.l, inimigo.a)){
			animacao_explosao();                      
			masked_blit(nave, buffer, explosao.wx = explosaoanimacao*102, explosao.wy, explosao.x = inimigo.x, explosao.y = inimigo.y, explosao.l, explosao.a);                      
			inimigo.x = 1000;
			inimigo.y = 1000;
			tiro2.x = 1000;
			tiro2.y = 1000; 
			atirar = 0;
			pontos++;
		}
      
		/*colisão do tiro do jogador no chefão*/
		if(colisao_tiro(tiro.x, tiro.y, tiro.l, tiro.a, chefao.x, chefao.y, chefao.l, chefao.a)){
			atirar = 0;
			chefaovida = chefaovida - 1;
        
			if(chefaovida==0){
				atirar = 0;               
				chefao.x = -1000;
				chefao.y = -1000;
				tiro3.x = 1000;
				tiro3.y = 1000;
				marcador = timerGame;
				chefaovida = -1;            
			}
		}
      
		/*COLISÃO -> INIMIGO VS JOGADOR*/ 
      
		/*colisão do tiro do ovni na nave do jogador*/
		if(colisao_tiro(tiro2.x, tiro2.y, tiro2.l, tiro2.a, jogador.x, jogador.y, jogador.l, jogador.a)){
			ovniatirar = 0;
			vidas = vidas -1;
		}
      
		/*colisão do tiro do chefão na nave do jogador*/
		if(colisao_tiro(tiro3.x, tiro3.y, tiro3.l, tiro3.a, jogador.x, jogador.y, jogador.l, jogador.a)){
			chefaoatirar = 0;
			vidas = vidas -1;
		} 
      
		/*COLISÃO ENTRE NAVES*/ 
      
		/*colisão do jogador na nave inimiga*/
		if(colisao_tiro(jogador.x, jogador.y, jogador.l, jogador.a, inimigo.x, inimigo.y, inimigo.l, inimigo.a)){
			inimigo.x = 1000;
			inimigo.y = 1000;
			vidas = vidas -1;
		}
      
		/*colisão do jogador na nave do chefão*/
		if(colisao_tiro(jogador.x, jogador.y, jogador.l, jogador.a, chefao.x, chefao.y, chefao.l, chefao.a)){
			vidas = vidas -1;
		}         
      
		/* limpando screen*/
		draw_sprite(screen, buffer, 0, 0);
		
		/* controlando o tempo do Jogo */
		//rest(20); utilizava essa função antes de implementar: tempoGame/timerGame/delayGame/;
		
		while(timerGame == delayGame){} //a mudança de quadro só ocorrerá quando timer possuir valor diferente de dalay;
		
		/* limpando o buffer */
		clear(buffer);
	}
   
	/* destruindo os BITMAPS*/
	destroy_bitmap(buffer);
	destroy_bitmap(cena1);
	destroy_bitmap(cena2);
	destroy_bitmap(cena3);
	destroy_bitmap(nave);
	destroy_bitmap(gameover);
	destroy_bitmap(finalizacao);
 
	deinit();
	return 0;
}
END_OF_MAIN()

//cabeçalho do programa.
void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	
	if (depth == 0) depth = 32;
	
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_timer();
	install_keyboard();
	install_mouse();
}

void deinit() {
	clear_keybuf();	
}

//movimento do cenário;
void movimento_cenario(){     
    if(cy1 > 600) cy1 = 0;
    if(cy2 > 600) cy2 = 0;
    if(cy3 > 600) cy3 = 0;
    cy1 += 12; 
    cy2 += 4; 
    cy3 += 8;     
}

//animação da turbina da nave;
void m_turbina(){
    turbina++;
	
    if(turbina>3){
        turbina = 0;           
    }
}

//movimento da nave do jogador;
void control(){
    
	/* importando efeitos sonoros*/ 
    SAMPLE *naveTiro = load_sample("som/laser_ gun_02.wav");
    
    //condição para se movimentar para esquerda; 
    if(key[KEY_LEFT]){
		jogador.x-= velocidade;
      
		//condição para impedir que a nave suma da tela;   
		if(jogador.x <= -50){
			jogador.x = -50;
		}                
    }
    
    //condição para se movimentar para direita;                  
    if(key[KEY_RIGHT]) {
		jogador.x+= velocidade;
    
		if(jogador.x >= 700){
			jogador.x = 700;
		}
    } 
    
    //condição para se movimentar para cima;  
    if(key[KEY_UP]){
		jogador.y-= velocidade;
    
		if(jogador.y <= 0){
			jogador.y = 0;
		}
    }
    
    //condição para se movimentar para baixo;
    if(key[KEY_DOWN]){
		jogador.y+= velocidade;
      
		if(jogador.y >= 430){
            jogador.y = 430;
		}    
    }
    
    //condição de atirar;
    if(key[KEY_Z])atirar = 1;
    
    //velocidade do tiro
    if(atirar) {
		play_sample(naveTiro, 255, 128, 5000, 0);         
		tiro.y -=30;
		tiro_animacao();
    }
    
    //recaregar tiro;
    //quando o tiro chegar ao topo da tela, sua variável é recaregada;
    if(tiro.y <= -50){
        atirar = 0;
    }
    
    //esconde o tiro debaixo da nave
    if(!atirar){               
		tiro.x = jogador.x+65;
		tiro.y = jogador.y+30; 
    }
    
}

//animação do tiro;
void tiro_animacao(){ 
    tiroanimacao++;
	
    if(tiroanimacao>3){
        tiroanimacao = 0;           
    }
}

//animação do tiro2;
void tiro2_animacao(){  
    tiro2animacao++;
	
    if(tiro2animacao>1){
        tiro2animacao = 0;           
    }
}

//animação do tiro3;
void tiro3_animacao(){
    tiro3animacao++;
    if(tiro3animacao>3){
        tiro3animacao = 0;           
    }
}

//condição de tiro do ovni;
void tiro_ovni(){
       
    /* importando efeitos sonoros*/ 
    //SAMPLE *naveTiro = load_sample("som/laser_ gun_02.wav");
              
    //condição de atirar;
    //if(inimigo.x == jogador.x)ovniatirar = 1;
    if((inimigo.x-30 <= jogador.x)&&(inimigo.x+30 > jogador.x))ovniatirar = 1;  
      
      //enquanto o ovni estiver na tela, ele atira
      //if(inimigo.x>-50 && inimigo.x<700 && inimigo.y>0 && inimigo.x<430) ovniatirar = 1;     
      
      //velocidade do tiro
    if(ovniatirar) {
        //play_sample(naveTiro, 255, 128, 5000, 0);         
        tiro2.y +=10;
        tiro2_animacao();
    }
      
    //recaregar tiro;
    //quando o tiro chegar ao fundo da tela, sua variável é recaregada;
    if(tiro2.y >= 700){
        ovniatirar = 0;
    }
      
    /*if(tiro2.x <= 50 || tiro2.x >= 700 || tiro2.y <= 0 || tiro2.y >= 430){
         ovniatirar = 0;
    }*/
      
    //esconde o tiro debaixo da nave
    if(!ovniatirar){               
        tiro2.x = inimigo.x+95;
        tiro2.y = inimigo.y+20; 
    }
}

//animação das luzes do ovni;
void luzes_ovni(){ 
    luz_ovni++;
	
    if(luz_ovni>5){
        luz_ovni = 0;           
    }
}

//movimento do ovni;
void movimento_ovni(){
	
    //determina uma posição aleátoria para o novo posicionamento da nave;
    int rx = 0;
    rx = rand()%600;
     
    //movimentando para baixo;
    inimigo.y+= 5;  
      
    //movimento da nave para a esquerda;
    if(ovnidirecao==0){
        inimigo.x-= 5;    
         
        if(inimigo.x <= 0){
            inimigo.x = 0;
            ovnidirecao = 1;
        }
    }
	   
	//movimento da nave para a direita;
	if(ovnidirecao==1){
		inimigo.x+= 5;
   	   
		if(inimigo.x >= 600){
            inimigo.x = 600;
            ovnidirecao = 0;
		}
	}
      
    //quando o ovni sumir da tela sumir da tela sua posição será reiniciada;
    if(inimigo.y >= 800){
        inimigo.x = rx;
        inimigo.y = -200;
    }
}

//animação do chefe dp game;
void luzes_chefe(){  
    luz_chefe++;
	
    if(luz_chefe>3){
        luz_chefe = 0;           
    }
}

//cria a colisão do tiro do jogador na nave inimiga;
int colisao_tiro(int ax, int ay, int al, int aa, int bx, int by, int bl, int ba){
    
    if(ax + al > bx && ax < bx + bl && ay + aa > by && ay < by + ba){
      return 1;
    }
    return 0; 
}

//animação daa explosão;
void animacao_explosao(){
    explosaoanimacao++;
	
    if(explosaoanimacao>8){
        explosaoanimacao = 0;
        explosao.y = 900;
        explosao.y = 900;           
    }         
}

/* iniciando a vida */
void vida_jogador(){
     
	for (int i=0; i<3; i++){
       vida[i].wx = 0;
       vida[i].wy = 1034;
       vida[i].x = 10 + i*36;
       vida[i].y = 570;
       vida[i].l = 36;
       vida[i].a = 26;
   }
}

void tiro_chefe(){
     
    if((chefao.x-30 <= jogador.x)&&(chefao.x+30 > jogador.x))chefaoatirar = 1;  
      
    //enquanto o chefão estiver na tela, ele atira
    //if(inimigo.x>-50 && inimigo.x<700 && inimigo.y>0 && inimigo.x<430) ovniatirar = 1;     
      
    //velocidade do tiro
    if(chefaoatirar) {
        //play_sample(naveTiro, 255, 128, 5000, 0);         
        tiro3.y +=chefaospeedtiro;
        tiro3_animacao();
        chefaotiro = chefaotiro + 1;
    }
      
    //recaregar tiro;
    //quando o tiro chegar ao fundo da tela, sua variável é recaregada;
    if(tiro3.y >= 700){
        chefaoatirar = 0;
    }
      
    //esconde o tiro debaixo da nave
    if(!chefaoatirar){               
        tiro3.x = chefao.x+95;
        tiro3.y = chefao.y+20; 
    }
}

//movimento do ovni;
void movimento_chefao(){
       
    //gatilho de chegada a tela;
    gatilho00();
       
    //gatilho para movimento esquerda e direita;
    gatilho01();
      
    gatilho02();
       
}

//descida do chefão na tela
void gatilho00(){
     
    //gatilho de chegada a tela;
    if (chefaogatilho == 0){
         
		//movimentando para baixo;
		chefao.y+= chefaospeedmove;
	
		if(chefao.y>=50){
            chefao.y=50;
            chefaogatilho = 1;
        }   
    }
}

//movimentação esquerda e direita do chefão
void gatilho01(){
     
    if (chefaogatilho == 1){  
         
        //movimento da nave para a esquerda;
        if(chefaodirecao==0){
			chefao.x-= chefaospeedmove;    
         
			if(chefao.x <= 0){
				chefao.x = 0;
				chefaodirecao = 1;
			}
         }
         
        //movimento da nave para a direita;
        if(chefaodirecao==1){
			chefao.x+= chefaospeedmove;
   	   
			if(chefao.x >= 600){
				chefao.x = 600;
				chefaodirecao = 0;
			}
        }
    }
}

//mudança de velocidade do chefão
void gatilho02(){
     
    if(chefaovida<7){
        chefaospeedtiro = 15; 
        chefaospeedmove = 10;
    }
     
    if(chefaovida<3){
        chefaospeedtiro = 20; 
        chefaospeedmove = 15;
    }  
}
