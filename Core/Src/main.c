/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "String.h"

#include "CO_app_STM32.h"
//#include "OD.h"

#include "math.h"
#include <stdio.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern OD_t *OD;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_CAN1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
void spara_indietro_usart(CAN_HandleTypeDef *hcan1);
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	/* USER CODE END Callback 0 */
	  if (htim->Instance == TIM14) {
	    HAL_IncTick();
	  }
	  /* USER CODE BEGIN Callback 1 */
    if (htim == canopenNodeSTM32->timerHandle) {
        canopen_app_interrupt();
    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t TxBuffer[50]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//variabili globali
uint8_t RxBuffer[50]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//sono buffers, vettori dove i messaggi inviati e ricevuti in seriale vangono immagazzinati per poi farci cose....

CAN_TxHeaderTypeDef TxHeader;//x inviare il messaggio
  CAN_RxHeaderTypeDef RxHeader;//per riceverlo

  CAN_TxHeaderTypeDef TxHeader2;//x inviare il messaggio
    CAN_RxHeaderTypeDef RxHeader2;//per riceverlo

  uint32_t TxMailbox;//è come se fosse la busta del messaggio....
  uint8_t TxData[8];//credo dei contenitori per i dati in IN e OUT
  uint8_t RxData[8];

  uint8_t TxData2[8];//credo dei contenitori per i dati in IN e OUT
  uint8_t RxData2[8];

  uint8_t count = 0;
  uint8_t counter=0;//contatore per vedere se passo da li

    //variablili per interrups di seriale
  	uint8_t pesi=0;
	uint8_t values[10];
	uint32_t value=0;
	HAL_StatusTypeDef stato;

	//Variabili per filtriCanBus
	uint32_t FilterSettings[14]; 					//Array in cui salvo i settaggi arrivati dalla Usart2 prima di inserirli nella stringa
	char FilterSetCanBus [10][30]={ 				//Array di stringhe i cui inserisco i valori di settaggio
		"CAN_FILTER_ENABLE",
		"0",
		"CAN_RX_FIFO0",
		"(0x102 >> 5) & 0xFFFF",
		"(0x102 & 0x1F) << 5",	// TODO
		"(0x7FF >> 5) & 0xFFFF",
		"(0x7FF & 0x1F) << 5",
		"CAN_FILTERMODE_IDMASK",
		"CAN_FILTERSCALE_32BIT",
		"14"
	};

int go=0;
int i=0;
int h=1;


//int j=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_USART2_UART_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_DMA(&huart2, RxBuffer, sizeof(RxBuffer));
     HAL_UART_Receive_IT(&huart2, RxBuffer, sizeof(RxBuffer));

     HAL_CAN_Start(&hcan1);


         HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//notifica di arrivo dato
         //HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);//notifica di arrivo dato
           //da quello che ho capito è una interrupt apposta per l'arrivo di un messaggio in can
           //chiedere cosa sono e come funzionano i tipi di interrupt che vuole....CAN_IT_RX_FIFO0_MSG_PENDING
           //quando arriva il messaggio, i dati passano per referenza dentro hcan
           TxHeader.ExtId = 0;
           TxHeader.IDE = CAN_ID_STD;
           TxHeader.TransmitGlobalTime = DISABLE;
           TxHeader.RTR = CAN_RTR_DATA;//definire se usiamo il remote frame o data frame
           TxHeader.DLC=8;
           TxData[0] = 0x01;
           TxData[1] = 0x02;
           TxData[2] = 0x03;
           TxData[3] = 0x04;
           TxData[4] = 0x05;
           TxData[6] = 0x06;
           TxData[5] = 0x06;
           TxData[7] = 0x07;

           HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);

           TxHeader2.ExtId = 0;
           TxHeader2.IDE = CAN_ID_STD;
           TxHeader2.TransmitGlobalTime = DISABLE;
           TxHeader2.RTR = CAN_RTR_DATA;//definire se usiamo il remote frame o data frame
           TxData2[0] = 0x01;
           TxData2[1] = 0x02;
           TxData2[2] = 0x03;
           TxData2[3] = 0x04;
           TxData2[4] = 0x05;
           TxData2[5] = 0x06;
           TxData2[7] = 0x07;
           //create instance canopen and init
           //most of the following functions does not overwrite the IOC settings
           //prima dell'init riesco a sparare qualsiasi messaggio can....quando arrivo acanopen_app_init(&canOpenNodeSTM32); non shotta piu niente
           CANopenNodeSTM32 canOpenNodeSTM32;
           canOpenNodeSTM32.CANHandle = &hcan1;
           canOpenNodeSTM32.HWInitFunction = MX_CAN1_Init;
           canOpenNodeSTM32.timerHandle = &htim14;
           canOpenNodeSTM32.desiredNodeID = 1;
           canOpenNodeSTM32.baudrate = 1000;

           canOpenNodeSTM32.activeNodeID=3;

           canopen_app_init(&canOpenNodeSTM32);
           HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
           OD_set_u32(OD_find(OD, 0x1802), 0x01, 3, false);//non funziona....hardware fault
//           int ciao = 5;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  canopen_app_process();//idem
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLRCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 8;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  CAN_FilterTypeDef canfilterconfig;
      canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
      canfilterconfig.FilterBank = 0;  // anything between 0 to SlaveStartFilterBank
      canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
      canfilterconfig.FilterIdHigh =(0x102 >> 5) & 0xFFFF;;
      canfilterconfig.FilterIdLow = (0x102 & 0x1F) << 5;
      canfilterconfig.FilterMaskIdHigh = (0x7FF >> 5) & 0xFFFF;
      canfilterconfig.FilterMaskIdLow = (0x7FF & 0x1F) << 5;
      canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;//due tipi di filtro
      canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
      canfilterconfig.SlaveStartFilterBank = 14;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assgned to CAN1
                  //meglio farselo spiegare.....    canfilterconfig.SlaveStartFilterBank = 13;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assgned to CAN1

      HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 0;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 65535;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void spara_indietro_usart(CAN_HandleTypeDef *hcan1)
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1)
  {
  	HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &RxHeader, RxData);
  	//TxHeader.StdId=2;
  	//h=2;

  	uint8_t newpesi=100;
  	uint8_t contatore=0;
  	int k=0;
  	for(k=0;contatore<RxHeader.DLC;k=k+1){
  		TxBuffer[k]= RxData[contatore]/newpesi;
  		if(newpesi==1){
  			newpesi=100;
  			contatore=contatore+1;

  		}else{
  			newpesi=newpesi/10;
  		}
  		if(k==49)break;
  	}
  	//TxBuffer=RxData;
  	TxBuffer[1]=RxData[1];
  	TxBuffer[0]=RxData[0];




  	HAL_UART_Transmit(&huart2, TxBuffer, sizeof(TxBuffer), 10);
  }
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	//counter=counter+1;
	for(i=0;i<50;i++){
		if(RxBuffer[i]=='e'){									//Valore terminale della stringa in arrivo nel caso in cui sia un DataFrame
		  go=1;
		  break;
		}
		if(RxBuffer[i]=='b'){									//Valore terminale della stringa in arrivo nel caso in cui sia il settaggio dei filtri CAN
		  go=2;
		  break;
		}
	}


	if(go==1 || go==2){

		for(int j=0;j<50;j++){									//scorro il buffer
			if(RxBuffer[j]=='a') {								//separatore di caratteri nella stringa

				for(int a=1;a<=pesi;a++){
					 RxBuffer[j]='\000';
					 RxBuffer[j]=0;
					 double power =pow((10),(pesi-a));
					 value =value +((power)*(values[a-1]));
					 values[a-1]=0;
				}

				pesi =0;

				if(go==1){  									//se è un dataframe salvo i valori su TxData
					switch (count){
						case (0):
							TxHeader.StdId=value;
						break;
						case (1):
							TxHeader.DLC =value;
						  break;
						case (2):
							TxData[0]=value;
						  break;
						case (3):
							TxData[1]=value;
						  break;
						case (4):
							TxData[2]=value;
						  break;
						case (5):
							TxData[3]=value;
						  break;
						case (6):
							TxData[4]=value;
						  break;
						case (7):
							TxData[5]=value;
						  break;
						case (8):
							TxData[6]=value;
						  break;
						case (9):
							TxData[7]=value;
						  break;
					}
				}
				if(go==2){										//se è il settaggio del filtro salvo tutti i dati su FilterSettings e poi li elaborerò alla fine della lettura del buffer
					switch (count){
						case (0): 								//seleziono se ho un ID extended (29bit) o standard (11bit)
							FilterSettings[0]=value;
							/*if(value==0){
								FilterSetCanBus[0]="CAN_FILTER_DISABLE";
							}
							else if(value==1){
								FilterSetCanBus[0]="CAN_FILTER_ENABLE";
							}*/
							break;
						case (1): 								//settaggio FIFO del filtro
							FilterSettings[1]=value;
							if(value==0){
								strcpy(FilterSetCanBus[2], "CAN_RX_FIFO0");

							}
							else if(value==1){
								strcpy(FilterSetCanBus[2], "CAN_RX_FIFO1");
							}
							break;
						case (2): 								//settaggio del FilterScale del filtro
							FilterSettings[2]=value;
							if(value==0){
								strcpy(FilterSetCanBus[8], "CAN_FILTERSCALE_16BIT");
							}
							else if(value==1){
								strcpy(FilterSetCanBus[8], "CAN_FILTERSCALE_32BIT");
							}
							break;
						case (3): 								//modalità di filtro: mask o list
							FilterSettings[3]=value;
							if(value==0){
								strcpy(FilterSetCanBus[7], "CAN_FILTERMODE_IDLIST");
							}
							else if(value==1){
								strcpy(FilterSetCanBus[7], "CAN_FILTERMODE_IDMASK");
							}
							break;
						case (4): 								//setto il Filter Bank
							FilterSettings[4]=value;
//							sprintf(FilterSetCanBus[1], "%u", value);
							break;
						case (5):								//Slave start filter Bank
							FilterSettings[5]=value;
//							sprintf(FilterSetCanBus[9], "%u", value);
							break;
						case (6):  								//Id (L'ID che accetto)
							FilterSettings[6]=value; 			//Mask
							break;
						case (7):  								//Shift HIGH Maschera
							FilterSettings[7]=value; 			//Shift High
							break;
						case (8): 								//Shift LOW Maschera
							FilterSettings[8]=value; 			//Shift Low
							break;
						case (9):  								//IdMask (la maschera che mi setta il filtro)
							FilterSettings[9]=value; 			//IdMask (valori 01)
							break;
						case (10):								//da qui in poi: valori aggiuntivi nel caso in cui volessi usare la modalità "list" del filtro. ci sono 4 possibili spazi per 4 possibili ID.
							FilterSettings[10]=value; 			//ID1
							break;
						case (11):
							FilterSettings[11]=value; 			//ID2
							break;
						case (12):
							FilterSettings[12]=value; 			//ID3
							break;
						case (13):
							FilterSettings[13]=value; 			//ID4
							break;
					}
				}

				value=0;
				count=count+1;
			}
			if((RxBuffer[j]<58)){
				if((RxBuffer[j]>47)){
				 values[pesi]=RxBuffer[j]-48;
				 pesi++;
				 RxBuffer[j]=0;
				 RxBuffer[j]='\000';
				}
			}
			if(RxBuffer[j]=='e'){	//se trovo il valore terminale della stringa di un dataframe allora procedo con l'invio tramite CAN
				go=0;
				RxBuffer[j]=0;
				RxBuffer[j]='\000';
				HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
				h=2;
				TxHeader2.DLC=TxHeader.DLC;
				TxHeader2.ExtId=TxHeader.ExtId;
				TxHeader2.IDE=TxHeader.IDE;
				TxHeader2.RTR=TxHeader.RTR;
				TxHeader2.StdId=TxHeader.StdId;
				TxHeader2.TransmitGlobalTime=TxHeader.TransmitGlobalTime;
				TxHeader.DLC = 8;
				count=0;
				break;
			}
			if(RxBuffer[j]=='b'){	//se trovo il valore terminale della stringa per il settaggio dei filtri allora procedo con l'elaborazione dei valori raccolti e li trasformo in stringhe.
				go=0;
				RxBuffer[j]=0;
				RxBuffer[j]='\000';



				  //FilterID High: creazione della stringa che mi setta nel filtro l'ID High dell'ID che deve essere verificato dal filtro.
				  char hex_IdMask[15]= {0};
//				  sprintf(hex_IdMask, "0x%X", FilterSettings[6]);  //trasformo il valore decimale ricevuto in Hex e poi prosegui concatenando stringhe
				  char Par[] = "(";

				  char Result[40]= {0};
				  strcat(Result, Par);
				  strcat(Result, hex_IdMask);
				  if(FilterSettings[0]==0){  							//se ho un ID extended
					  char Shifh[] = " >> 13) & 0xFFFF";
					  strcat(Result, Shifh);}
				  if(FilterSettings[0]==1){  							//se ho un standard ID
					  char Shifh[] = " >> 5) & 0xFFFF";
					  strcat(Result, Shifh);}
				  strcpy(FilterSetCanBus[3], Result); //Result è la stringa finale che salvo dentro a FilterSetCanBus e che setterà il filtro con i valori ricevuti

				  memset(Result, 0, sizeof(Result)); //ripulisco Result


				  //FilterID Low: imposto la seconda parte dei 16 bit dell'ID
				  strcat(Result, Par);
				  strcat(Result, hex_IdMask);
				  if(FilterSettings[0]==0){//se ho un ID extended
					  char Shifl[] = "<< 3) 0xFFFF";
					  strcat(Result, Shifl);}
				  if(FilterSettings[0]==1){//se ho un standard ID
					  char Shifl[] = " & 0x1F) << 5";
					  strcat(Result, Shifl);}

				  strcpy(FilterSetCanBus[4], Result);//salvo la stringa elaborata su FilterSetCanBus

				  memset(Result, 0, sizeof(Result));//ripulisco Result


				  //MaskIdHigh: concateno la maschera con i valori di shift che invio
				  char hex_Mask[15]= {0};
//				  sprintf(hex_Mask, "0x%X", FilterSettings[9]); //id maschera
				  char Shifh[] = " >> ";
				  char valoreShiftH[15]= {0};
//				  sprintf(valoreShiftH, "%u", FilterSettings[7]); //valore di shift High
				  char fine[] = ") & 0xFFFF";
				  strcat(Result, Par);
				  strcat(Result, hex_Mask);
				  strcat(Result, Shifh);
				  strcat(Result, valoreShiftH);
				  strcat(Result, fine);
				  strcpy(FilterSetCanBus[5], Result);//salvo la stringa elaborata su FilterSetCanBus

				  memset(Result, 0, sizeof(Result));//ripulisco Result


				  //MakIdLow
				  char valoreShiftL[15]= {0};
//				  sprintf(valoreShiftL, "%u", FilterSettings[8]);
				  strcat(Result, Par);
				  strcat(Result, hex_Mask);
				  if(FilterSettings[0]==0){ //se ho extended ID
					  char mezz[] = " << ";
				  	  strcat(Result, mezz);
				  	  strcat(Result, valoreShiftL); //valore di shift LOW
				  	  char end[] = ")& 0xFFFF";
				  	  strcat(Result, end);}

				  if(FilterSettings[0]==1){ //se ho standard ID
					  char mezz[] = " & 0x1F) << ";
					  strcat(Result, mezz);
					  strcat(Result, valoreShiftL); //valore di shift LOW
				  }

				  strcpy(FilterSetCanBus[6], Result);//salvo la stringa elaborata su FilterSetCanBus
				  memset(Result, 0, sizeof(Result));//ripulisco Result


//				CAN_FilterTypeDef canfilterconfig; //setto i filtri
//				canfilterconfig.FilterActivation = FilterSetCanBus[0];
//				canfilterconfig.FilterBank = FilterSetCanBus[1];
//				canfilterconfig.FilterFIFOAssignment = FilterSetCanBus[2];
//				canfilterconfig.FilterIdHigh =FilterSetCanBus[3];
//				canfilterconfig.FilterIdLow = FilterSetCanBus[4];
//				canfilterconfig.FilterMaskIdHigh = FilterSetCanBus[5];
//				canfilterconfig.FilterMaskIdLow = FilterSetCanBus[6];
//				canfilterconfig.FilterMode = FilterSetCanBus[7];
//				canfilterconfig.FilterScale = FilterSetCanBus[8];
//				canfilterconfig.SlaveStartFilterBank = FilterSetCanBus[9];
//				HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
				count=0;
				break;
			}
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
