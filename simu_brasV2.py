import numpy as np
import matplotlib.pyplot as plt

# ======================
# PARAMÈTRES
# ======================

L = 15
R = 17
offset_x = 15
offset_y = 3

theta1 = 107
theta2 = 17

#theta2 = theta2 + R

theta1 = theta1 * np.pi / 180
theta2 = theta2 * np.pi / 180



# ======================
# CINÉMATIQUE DIRECTE
# ======================

def compute_positions(theta1, theta2):
    x1 = offset_x + L * np.cos(theta1)
    y1 = offset_y + L * np.sin(theta1)

    x2 = x1 + L * -np.cos(theta1 - -np.pi - theta2)
    y2 = y1 + L * np.sin(theta1 - -np.pi - theta2)

    return x1, y1, x2, y2


# ======================
# AFFICHAGE
# ======================

fig, ax = plt.subplots()

if theta1 is None:
    theta1, theta2 = 0, 0

x1, y1, x2, y2 = compute_positions(theta1, theta2)

line, = ax.plot([offset_x, x1, x2], [offset_y, y1, y2], 'o-', lw=4)
target, = ax.plot(x2, y2, 'rx')
base_point, = ax.plot(offset_x, offset_y, 'ko')

# texte affichage coordonnées
text = ax.text(-15, 37, '', fontsize=12)

ax.set_xlim(-17, 35)
ax.set_ylim(-1, 35)
ax.set_aspect('equal')
ax.grid()

# ligne sol
ax.axhline(0)


# ======================
# UPDATE
# ======================

def update():
    
    if theta1 is None:
        return

    x1, y1, x2, y2 = compute_positions(theta1, theta2)

    line.set_data([offset_x, x1, x2], [offset_y, y1, y2])
    target.set_data([x2], [y2])


    text.set_text(f"X = {x2:.2f}   Y = {y2:.2f}")

    fig.canvas.draw_idle()

# initial update
update()

# ======================
# LANCEMENT
# ======================

plt.show()
