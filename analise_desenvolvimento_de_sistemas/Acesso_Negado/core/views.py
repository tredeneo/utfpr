from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import login, authenticate
from django.contrib.auth.decorators import login_required
from .forms import SignUpForm, CadastroJogoForm, ComentarioForm
from django.views.generic.edit import CreateView
from .models import Jogo, Descricao
from django.urls import reverse_lazy
from django.views.generic.detail import DetailView
from django.views.generic.list import ListView
from django.contrib.auth.models import User

def signup(request):
    if(request.method == 'POST'):
        form = SignUpForm(request.POST)
        if(form.is_valid()):
            user = form.save()
            user.refresh_from_db()              #Carrega a instância de profile criada pelo sinal(@receiver)
            user.profile.deficiencia = form.cleaned_data.get('deficiencia')
            user.save()
            #username = form.cleaned_data.get('username')
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=user.username, password=raw_password)
            login(request, user)
            return redirect('home')
    else:
        form = SignUpForm()
    return render(request, 'signup.html', {'form':form})

#@login_required
#def home(request):
    #return render(request, 'home.html')

@login_required(login_url = '/core/')   #Se o usuário ainda não estiver logado, volte para 'home'
def cadastrojogo(request):
    if(request.method == 'POST'):
        form = CadastroJogoForm(request.POST, request.FILES)
        if(form.is_valid()):
            jogo = form.save(commit = False)
            jogo.user = request.user
            #jogo.imagem = request.FILES['']
            jogo = form.save()
            jogo.refresh_from_db()
            jogo.descricao.texto = form.cleaned_data.get('texto')
            jogo.save()
            return redirect('home')
    else:
        form = CadastroJogoForm()
    return render(request, 'CadastroJogo.html', {'form':form})

def add_comentario(request, pk):
    jogo = get_object_or_404(Jogo, pk = pk)
    if(request.method == 'POST'):
        form = ComentarioForm(request.POST)
        if(form.is_valid()):
            comentario = form.save(commit = False)
            comentario.jogo = jogo
            comentario.dono = request.user
            comentario.save()
            return redirect('home')
    else:
        form = ComentarioForm()
    return render(request, 'CriandoComentario.html', {'form':form})


class JogoDetailView(DetailView):
    model = Jogo
    template_name = 'JogoDetail.html'
    context_object_name = 'Jogo'

class JogoListView(ListView):
    model = Jogo
    template_name = 'JogoList.html'
    context_object_name = 'JogoList'

class UserDetailView(DetailView):
    model = User
    template_name = 'UserDetail.html'
    context_object_name = 'usuario'


    #def get_context_data(self, **kwargs):
        #context = super().get_context_data(**kwargs)
        #context['jogos_cadastrados'] = Jogo.objects.all().filter(user = self.kwargs.get('id'))

########################################
#class JogoCreate(CreateView):
    #model = Jogo
    #form_class = CadastroJogoForm
    #def get_initial(self):
        #initial = super().get_initial()
        #initial = ['user'] = self.request.user.id
        #initiaç = ['descricao'] = self.request.descricao

    #fields = ['nome', 'criador_do_post', 'pagina_do_jogo']
    #success_url = reverse_lazy('home')
    #template_name = 'CadastroJogo.html'
