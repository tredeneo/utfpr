from django import forms
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.contrib.auth import get_user_model
from .models import Descricao, Jogo, Comentarios

class SignUpForm(UserCreationForm):
    deficiencia = forms.CharField(max_length = 20, required = False, help_text = 'Opcional*')
    #first_name = forms.CharField(max_length = 20, required = False, help_text = 'Opcional*')
    #last_name = forms.CharField(max_length = 20, required = False, help_text = 'Opcional*')
    #email = forms.EmailField(max_length = 100, help_text = 'Obrigatório*')
    class Meta:
        model = User
        fields = ('username','deficiencia','password1','password2')

class CadastroJogoForm(forms.ModelForm):
    texto = forms.CharField(max_length = 5000, widget = forms.Textarea)
    imagem = forms.ImageField()
    class Meta:
        model = Jogo
        fields = ('nome', 'pagina_do_jogo', 'texto', 'imagem')

    #def save(self, *args, **kwargs):
        #self.instance.user

class ComentarioForm(forms.ModelForm):
    comentario = forms.CharField(max_length = 2000, widget = forms.Textarea)
    class Meta:
        model = Comentarios
        fields = ('comentario', 'nota_fisica', 'nota_visual', 'nota_auditiva')
