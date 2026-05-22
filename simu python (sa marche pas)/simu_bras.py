import numpy as np
import matplotlib.pyplot as plt

# ======================
# PARAMÈTRES
# ======================

L = 15
offset_x = 0
offset_y = 3

# position initiale
X = 3
Y = 4

step = 0.2  # vitesse déplacement

# ======================
# CINÉMATIQUE INVERSE
# ======================

def compute_angles(X, Y):
    Xr = X - offset_x
    Yr = Y - offset_y

    alpha = np.arctan2(Yr, Xr)

    d = np.sqrt(Xr**2 + Yr**2)

    d_2 = d / 2

    if d > 2 * L:
        return None, None

    val = (Xr**2 + Yr**2 - 2 * L**2) / (2 * L**2)

    # coude vers le bas
    theta2 = -np.arccos(val)

    theta1 = np.arctan2(Yr, Xr) - np.arctan2(L * np.sin(theta2), L + L * np.cos(theta2))
    print(f"theta1: {np.degrees(theta1):.2f}°   theta2: {np.abs(np.degrees(theta2)):.2f}°")

    return theta1, theta2


# ======================
# CINÉMATIQUE DIRECTE
# ======================

def compute_positions(theta1, theta2):
    x1 = offset_x + L * np.cos(theta1)
    y1 = offset_y + L * np.sin(theta1)

    x2 = x1 + L * np.cos(theta1 + theta2)
    y2 = y1 + L * np.sin(theta1 + theta2)

    return x1, y1, x2, y2


# ======================
# AFFICHAGE
# ======================

fig, ax = plt.subplots()

theta1, theta2 = compute_angles(X, Y)

if theta1 is None:
    theta1, theta2 = 0, 0

x1, y1, x2, y2 = compute_positions(theta1, theta2)

line, = ax.plot([offset_x, x1, x2], [offset_y, y1, y2], 'o-', lw=4)
target, = ax.plot(X, Y, 'rx')
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
    global X, Y

    theta1, theta2 = compute_angles(X, Y)

    if theta1 is None:
        return

    x1, y1, x2, y2 = compute_positions(theta1, theta2)

    line.set_data([offset_x, x1, x2], [offset_y, y1, y2])
    target.set_data([X], [Y])


    text.set_text(f"X = {X:.2f}   Y = {Y:.2f}")

    fig.canvas.draw_idle()


# ======================
# CONTRÔLE CLAVIER
# ======================

def on_key(event):
    global X, Y

    if event.key == 'up':
        if Y + step >= 0:
            Y += step

    elif event.key == 'down':
        if Y - step >= 0:
            Y -= step

    elif event.key == 'left':
        if X - step >= 0:
            X -= step

    elif event.key == 'right':
        if X + step >= 0:
            X += step

    update()


fig.canvas.mpl_connect('key_press_event', on_key)

# initial update
update()

# ======================
# LANCEMENT
# ======================

plt.show()
