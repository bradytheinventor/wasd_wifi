import socket, sys
import pygame

HOST = '192.168.1.1'
PORT = 288

pygame.init()
canvas = pygame.display.set_mode((640, 480))
pygame.display.set_caption("Ye Olde Dueling CyBots")

fps_clock = pygame.time.Clock()

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(1)
    s.connect((HOST, PORT))

except socket.error as e:
    print(e)


def send_char(char):
    try:
        s.sendall(char.encode())
        
    except socket.error as e:
        print(e)  


running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
                break

            elif event.key == pygame.K_w:
                send_char('w')

            elif event.key == pygame.K_a:
                send_char('a')

            elif event.key == pygame.K_s:
                send_char('s')

            elif event.key == pygame.K_d:
                send_char('d')

            elif event.key == pygame.K_q:
                send_char('q')

            elif event.key == pygame.K_SPACE:
                send_char(' ')

            #enter high speed mode
            elif event.key == pygame.K_LCTRL:
                send_char('y')

            #enter low speed mode
            elif event.key == pygame.K_LSHIFT:
                send_char('n')

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_w:
                #allow small adjustments with a and d
                if pygame.key.get_pressed()[pygame.K_a]:
                    send_char('a')

                elif pygame.key.get_pressed()[pygame.K_d]:
                    send_char('d')

                else:
                    send_char(' ')

            elif event.key == pygame.K_a:
                #allow transitions from w and s to a
                if pygame.key.get_pressed()[pygame.K_w]:
                    send_char('w')

                elif pygame.key.get_pressed()[pygame.K_s]:
                    send_char('s')

                else:
                    send_char(' ')

            elif event.key == pygame.K_s:
                #allow small adjustments with a and d
                if pygame.key.get_pressed()[pygame.K_a]:
                    send_char('a')

                elif pygame.key.get_pressed()[pygame.K_d]:
                    send_char('d')

                else:
                    send_char(' ')

            elif event.key == pygame.K_d:
                #allow transitions from w and s to d
                if pygame.key.get_pressed()[pygame.K_w]:
                    send_char('w')

                elif pygame.key.get_pressed()[pygame.K_s]:
                    send_char('s')

                else:
                    send_char(' ')

            #exit high or low speed modes
            elif event.key == pygame.K_LSHIFT:
                send_char('h')

            elif event.key == pygame.K_LCTRL:
                send_char('h')

    #tick clock and update display
    fps_clock.tick(60)
    pygame.display.update()
    canvas.fill((0, 0, 0))

#end program if ESC or the red 'x' is pressed
pygame.quit()

try:
    s.close()
    
except socket.error as e:
    print(e)
