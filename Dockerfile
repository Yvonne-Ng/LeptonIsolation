From atlasml/ml-base
WORKDIR ../../../data/leptonisolation/LeptonIsolation/
RUN pip install -r requirements.txt --user
CMD ["python3", "isolation.py"]

