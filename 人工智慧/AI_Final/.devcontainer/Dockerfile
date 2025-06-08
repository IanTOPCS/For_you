FROM tensorflow/tensorflow:nightly-gpu-jupyter

ARG USERNAME=devuser
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update && apt-get install -y sudo python3-pip \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN pip3 install --upgrade pip

RUN pip3 install \
    jupyterlab \
    matplotlib \
    seaborn \
    pandas \
    scikit-learn \
    keras \
    ipython \
    ipywidgets \
    xgboost

USER $USERNAME
