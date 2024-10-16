#include <avr/io.h>
#include <util/delay.h>

// Function prototypes
void uart_init(unsigned int baud);
void uart_transmit(char data);
void uart_print_string(const char *str);
void uart_receive_string(char *buffer, uint8_t max_length);

#define MAX_STRING_LENGTH 50 // Maximum length of the input string

int main(void) {
    uart_init(9600); // Initialize UART at 9600 baud

    char received_string[MAX_STRING_LENGTH]; // Buffer to hold received string

    while (1) {
        uart_receive_string(received_string, MAX_STRING_LENGTH); // Receive a string
        uart_print_string(received_string); // Print the received string
        _delay_ms(1000); // Wait for a second before the next iteration
    }
}

void uart_init(unsigned int baud) {
    // Set baud rate
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8data, 1stop bit
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_transmit(char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    // Put data into buffer, sends the data
    UDR0 = data;
}

void uart_print_string(const char *str) {
    while (*str) {
        uart_transmit(*str++); // Transmit each character in the string
    }
    uart_transmit('\n'); // Add a newline after the string
}

void uart_receive_string(char *buffer, uint8_t max_length) {
    uint8_t i = 0;
    char ch;

    while (i < max_length - 1) { // Leave space for null terminator
        // Wait for character to be received
        while (!(UCSR0A & (1 << RXC0)));

        // Get and return received data from buffer
        ch = UDR0;

        // Check for newline character
        if (ch == '\n') {
            break; // End the input on newline
        }

        buffer[i++] = ch; // Store character in buffer
    }
    buffer[i] = '\0'; // Null-terminate the string
}

