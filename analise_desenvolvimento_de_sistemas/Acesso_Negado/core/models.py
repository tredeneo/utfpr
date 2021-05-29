from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver

class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    deficiencia = models.CharField(max_length = 20, blank = True) #criar uma lista de opções e talvez inserir alguns atributos

    def __str__(self):
        return self.user.username

@receiver(post_save, sender = User)
def update_user_profile(sender, instance, created, **kwargs):
    if(created):
        Profile.objects.create(user = instance)
    instance.profile.save()

class Jogo(models.Model):
    nome = models.CharField(max_length = 60)
    #imagem
    user = models.ForeignKey(User, on_delete = models.CASCADE)
    pagina_do_jogo = models.URLField(max_length = 100)
    data_criacao = models.DateTimeField(auto_now = True)
    imagem = models.ImageField(upload_to = 'jogos/', max_length = 255)
    #gênero = ...

    def __str__(self):
        return self.nome

class Descricao(models.Model):
    texto = models.TextField(max_length = 5000)
    jogo = models.OneToOneField(Jogo, on_delete = models.CASCADE)


@receiver(post_save, sender = Jogo)
def update_jogo_descricao(sender, instance, created, **kwargs):
    if(created):
        Descricao.objects.create(jogo = instance)
    instance.descricao.save()

class Comentarios(models.Model):
    dono = models.ForeignKey(User, on_delete = models.CASCADE)
    jogo = models.ForeignKey(Jogo, on_delete = models.CASCADE, related_name = 'comentarios')
    comentario = models.TextField(max_length = 2000)
    nota_fisica = models.PositiveIntegerField(max_length = 2, )
    nota_visual = models.IntegerField(max_length = 2)
    nota_auditiva = models.IntegerField(max_length = 2)

    def __str__(self):
        return self.comentario
