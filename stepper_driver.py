# Importing Libraries
import serial
import time
import click

@click.command()
@click.option('--name', prompt='Your name', help='The person to greet.')
@click.option('--count', default=1, help='Number of greetings.')
def greet(name, count):
    """Simple program that greets NAME for a total of COUNT times."""
    for _ in range(count):
        click.echo(f"Hello, {name}!")
        
    try:
        arduino = AutoFocuser()
        while True:
            num = input("Enter a number: ")
            value = arduino.write_read(num)
            print(value)  # printing the value
    except KeyboardInterrupt:
        print("\nProgram Interrupted")
        arduino.close()

class AutoFocuser:
    def __init__(self):
        self.arduino = serial.Serial(port="/dev/ttyUSB0", baudrate=115200, timeout=0.1)
        time.sleep(2)
        print("Connection Established")

    def write_read(self, x):
        self.arduino.write(bytes(x, "utf-8"))
        time.sleep(0.05)
        data = self.arduino.readline()
        return data

    def move(self, steps):
        value = self.write_read(str(steps))
        return value

    def close(self):
        self.arduino.close()
        print("Connection Closed")

if __name__=="__main__":
    greet()

