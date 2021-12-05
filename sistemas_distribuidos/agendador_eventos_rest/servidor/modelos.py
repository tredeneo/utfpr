from typing import Dict, List, Tuple
import uuid
import datetime
from dataclasses import dataclass, field


@dataclass
class Enquete:
    id: str
    criador: str
    titulo: str
    local: str
    datas: List[Dict[datetime.datetime, int]]
    limite: datetime.datetime
    estado: str
    participantes: List[str]

    def __init__(self, json):
        self.id = str(uuid.uuid4())
        self.criador = json["criador"]
        self.titulo = json["titulo"]
        self.local = json["local"]
        self.limite = datetime.datetime.fromisoformat(json["limite"])
        self.estado = json["estado"]
        self.participantes = [self.criador]
        self.datas = self.pegar_datas(json["datas"])

    def votar(self, json: str):
        data = self.pegar_datas(json["datas"])
        for i in range(len(self.datas)):
            for j in data:
                if self.datas[i]["data"] == j["data"]:
                    self.datas[i]["votos"] += 1

    def pegar_datas(self, json) -> List[Dict[datetime.datetime, int]]:
        datas: List[Dict[datetime.datetime, int]] = []
        for i in json:
            data = {
                "data": datetime.datetime.fromisoformat(i["data"]),
                "votos": i["votos"],
            }
            datas.append(data)
        return datas

    def procurar_partipante(self, usuarios: List[object]):
        for i in usuarios:
            pass


@dataclass
class Usuario:
    nome: str

    def __init__(self, json):
        self.nome = json["nome"]
