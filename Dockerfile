FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

# Installer Qt6 + outils + dépendances OpenGL et X11
RUN apt-get update && apt-get install -y \
    build-essential cmake \
    qt6-base-dev qt6-tools-dev qt6-tools-dev-tools \
    libqt6gui6 libqt6widgets6 \
    libglu1-mesa-dev freeglut3-dev mesa-common-dev \
    libx11-dev libxext-dev libxkbcommon-dev libxkbcommon-x11-dev \
    # dépendances du plugin xcb
    libxcb-xinerama0 \
    libxkbcommon-x11-0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libxcb-xfixes0 \
    libxcb-shape0 \
    libxcb-randr0 \
    libxcb-util1 \
    x11-xserver-utils \
    fonts-dejavu-core \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

# Configurer et compiler le projet
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
RUN cmake --build build -j$(nproc)

# Éviter les problèmes mémoire Qt/X11
ENV QT_X11_NO_MITSHM=1

# Commande par défaut : lancer ton appli
CMD ["./build/owloApp"]
