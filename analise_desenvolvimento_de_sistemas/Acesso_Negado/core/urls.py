from django.contrib import admin
from django.urls import path, include
from . import views as core_views
from django.contrib.auth import views as auth_views
from django.contrib.auth.models import User
from django.views.generic.detail import DetailView
from django.conf.urls.static import static
from django.conf import settings

urlpatterns = [
    #path('admin/', admin.site.urls),
    path('', core_views.JogoListView.as_view(), name = 'home'),
    path('login/', auth_views.LoginView.as_view(template_name = 'login.html'), name = 'login'),
    path('logout/', auth_views.LogoutView.as_view(next_page = 'login'), name = 'logout'),
    path('signup/', core_views.signup, name = 'signup'),
    path('CadastrarJogo/', core_views.cadastrojogo, name = 'CadastrarJogo'),
    path('visualizarJogo/<int:pk>', core_views.JogoDetailView.as_view(), name = 'JogoDetailView'),
    path('visualizarUser/<int:pk>', core_views.UserDetailView.as_view(), name = 'UserDetailView'),
    path('visualizarJogo/<int:pk>/Comentario', core_views.add_comentario, name = 'add_comentario'),
] + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT)
