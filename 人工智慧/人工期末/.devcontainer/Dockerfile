FROM tensorflow/tensorflow:nightly-gpu-jupyter

# 建立使用者
ARG USERNAME=devuser
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update && apt-get install -y sudo \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# 安裝 Python 開發環境（可依需求調整）
RUN apt-get update && apt-get install -y wget curl gnupg2 software-properties-common

RUN pip install -U pip && pip install \
    jupyterlab \
    matplotlib \
    seaborn \
    pandas \
    scikit-learn \
    keras

CMD ["python3", "-c", "import tensorflow as tf; print(tf.config.list_physical_devices('GPU'))"]

# 使用非 root 使用者
USER $USERNAME