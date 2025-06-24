/*
 * SPI_Cfg.h
 *
 *  Created on: Mar 14, 2025
 *      Author: moham
 */

#ifndef SPI_CFG_H_
#define SPI_CFG_H_


/*Select Master/Slave
 * 										    	1. SPI_MASTER
 * 										     	2. SPI_SLAVE
 */
#define SPI_MASTER_SLAVE_SELECT			SPI_MASTER


 /* Select Interrupt mode:
 * 												1- INT_DISABLED
									     		2- INT_ENABLED
 */
#define SPI_INT_MODE	                INT_DISABLED

/*Set SPI Enable
 *											     1. SPI_DISABLED
 * 												 2. SPI_ENABLED
 */
#define SPI_ENABLE_MODE					SPI_ENABLED


/*
 * Select Data order mode:
 * 			 									1- LSB_FIRST
 *          								    2- MSB_FIRST
 * */
#define SPI_DATA_ORDER					MSB_FIRST

/*Select clock polarity mode:
 * 												1-  SPI_RISING_LEADING_FALLING_TRAILING
 * 		          							    2- SPI_FALLING_LEADING_RISING_TRAILING
 *
 * */
#define SPI_CLK_POLARITY	            SPI_RISING_LEADING_FALLING_TRAILING


/*Select clock phase mode:
 * 												1- SAMPLE_LEADING_SETUP_TRAILING
 *            								    2- SETUP_LEADING_SAMPLE_TRAILING
 * 	*/
#define SPI_CLK_PHASE                   SAMPLE_LEADING_SETUP_TRAILING


/*Set Clock Rate Divide
*											   1. FREQ_DIVIDED_BY_2
*						  		  			   2. FREQ_DIVIDED_BY_4
*						  		  			   3. FREQ_DIVIDED_BY_8
*						  		  			   4. FREQ_DIVIDED_BY_16
*						  		  			   5. FREQ_DIVIDED_BY_32
*						  		  			   6. FREQ_DIVIDED_BY_64
*							  			       7. FREQ_DIVIDED_BY_128
 */
#define SPI_CLOCK_RATE			      		 FREQ_DIVIDED_BY_16



/*Set Timeout for your functions*/
#define SPI_u32TIMEOUT					10000UL

#endif /* SPI_CFG_H_ */
